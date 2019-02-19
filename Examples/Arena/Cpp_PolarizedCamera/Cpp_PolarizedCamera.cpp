/***************************************************************************************
***                                                                                 ***
***  Copyright (c) 2018, Lucid Vision Labs, Inc.                                    ***
***                                                                                 ***
***  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     ***
***  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       ***
***  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    ***
***  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         ***
***  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ***
***  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  ***
***  SOFTWARE.                                                                      ***
***                                                                                 ***
***************************************************************************************/

#include "stdafx.h"
#include "ArenaApi.h"
#include "SaveApi.h"

#define _USE_MATH_DEFINES
#include <math.h>

#if defined __linux__
#include <algorithm>
#define max std::max
#endif

#define TAB1 "  "
#define TAB2 "    "

// Polarization: Introduction
//    This example demonstrates the different ways of processing image data
//    from a polarized sensor camera.

#define TIMEOUT 2000

enum ProcessedPolarizedImage
{
	AoLP,
	DoLP,
	Deg2x2,
	HSV,
	Raw
};

std::string ProcessedPolarizedImageString[] =
{
	"AoLP",
	"DoLP",
	"Deg2x2",
	"HSV",
	"Raw"
};

// RGB color map
// Note: This table is stored in memory as little-endian on Windows
const uint32_t polar_color_table[] = {
	0xFF0000, 0xFF0600, 0xFF0C00, 0xFF1200, 0xFF1800, 0xFF1E00, 0xFF2400, 0xFF2A00, 0xFF3000, 0xFF3600,
	0xFF3C00, 0xFF4200, 0xFF4800, 0xFF4E00, 0xFF5400, 0xFF5A00, 0xFF6000, 0xFF6600, 0xFF6C00, 0xFF7200,
	0xFF7800, 0xFF7E00, 0xFF8400, 0xFF8A00, 0xFF9000, 0xFF9600, 0xFF9C00, 0xFFA200, 0xFFA800, 0xFFAE00,
	0xFFB400, 0xFFBA00, 0xFFC000, 0xFFC600, 0xFFCC00, 0xFFD200, 0xFFD800, 0xFFDE00, 0xFFE400, 0xFFEA00,
	0xFFF000, 0xFFF600, 0xFFFC00, 0xFCFF00, 0xF6FF00, 0xF0FF00, 0xEAFF00, 0xE4FF00, 0xDEFF00, 0xD8FF00,
	0xD2FF00, 0xCCFF00, 0xC6FF00, 0xC0FF00, 0xBAFF00, 0xB4FF00, 0xAEFF00, 0xA8FF00, 0xA2FF00, 0x9CFF00,
	0x96FF00, 0x90FF00, 0x8AFF00, 0x84FF00, 0x7EFF00, 0x78FF00, 0x72FF00, 0x6CFF00, 0x66FF00, 0x60FF00,
	0x5AFF00, 0x54FF00, 0x4EFF00, 0x48FF00, 0x42FF00, 0x3CFF00, 0x36FF00, 0x30FF00, 0x2AFF00, 0x24FF00,
	0x1EFF00, 0x18FF00, 0x12FF00, 0x0CFF00, 0x06FF00, 0x00FF00, 0x00FF06, 0x00FF0C, 0x00FF12, 0x00FF18,
	0x00FF1E, 0x00FF24, 0x00FF2A, 0x00FF30, 0x00FF36, 0x00FF3C, 0x00FF42, 0x00FF48, 0x00FF4E, 0x00FF54,
	0x00FF5A, 0x00FF60, 0x00FF66, 0x00FF6C, 0x00FF72, 0x00FF78, 0x00FF7E, 0x00FF84, 0x00FF8A, 0x00FF90,
	0x00FF96, 0x00FF9C, 0x00FFA2, 0x00FFA8, 0x00FFAE, 0x00FFB4, 0x00FFBA, 0x00FFC0, 0x00FFC6, 0x00FFCC,
	0x00FFD2, 0x00FFD8, 0x00FFDE, 0x00FFE4, 0x00FFEA, 0x00FFF0, 0x00FFF6, 0x00FFFC, 0x00FCFF, 0x00F6FF,
	0x00F0FF, 0x00EAFF, 0x00E4FF, 0x00DEFF, 0x00D8FF, 0x00D2FF, 0x00CCFF, 0x00C6FF, 0x00C0FF, 0x00BAFF,
	0x00B4FF, 0x00AEFF, 0x00A8FF, 0x00A2FF, 0x009CFF, 0x0096FF, 0x0090FF, 0x008AFF, 0x0084FF, 0x007EFF,
	0x0078FF, 0x0072FF, 0x006CFF, 0x0066FF, 0x0060FF, 0x005AFF, 0x0054FF, 0x004EFF, 0x0048FF, 0x0042FF,
	0x003CFF, 0x0036FF, 0x0030FF, 0x002AFF, 0x0024FF, 0x001EFF, 0x0018FF, 0x0012FF, 0x000CFF, 0x0006FF,
	0x0000FF, 0x0600FF, 0x0C00FF, 0x1200FF, 0x1800FF, 0x1E00FF, 0x2400FF, 0x2A00FF, 0x3000FF, 0x3600FF,
	0x3C00FF, 0x4200FF, 0x4800FF, 0x4E00FF, 0x5400FF, 0x5A00FF, 0x6000FF, 0x6600FF, 0x6C00FF, 0x7200FF,
	0x7800FF, 0x7E00FF, 0x8400FF, 0x8A00FF, 0x9000FF, 0x9600FF, 0x9C00FF, 0xA200FF, 0xA800FF, 0xAE00FF,
	0xB400FF, 0xBA00FF, 0xC000FF, 0xC600FF, 0xCC00FF, 0xD200FF, 0xD800FF, 0xDE00FF, 0xE400FF, 0xEA00FF,
	0xF000FF, 0xF600FF, 0xFC00FF, 0xFF00FC, 0xFF00F6, 0xFF00F0, 0xFF00EA, 0xFF00E4, 0xFF00DE, 0xFF00D8,
	0xFF00D2, 0xFF00CC, 0xFF00C6, 0xFF00C0, 0xFF00BA, 0xFF00B4, 0xFF00AE, 0xFF00A8, 0xFF00A2, 0xFF009C,
	0xFF0096, 0xFF0090, 0xFF008A, 0xFF0084, 0xFF007E, 0xFF0078, 0xFF0072, 0xFF006C, 0xFF0066, 0xFF0060,
	0xFF005A, 0xFF0054, 0xFF004E, 0xFF0048, 0xFF0042, 0xFF003C, 0xFF0036, 0xFF0030, 0xFF002A, 0xFF0024,
	0xFF001E, 0xFF0018, 0xFF0012, 0xFF000C, 0xFF0006, 0xFF0000
};

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

void saveRAWInputImage(Arena::IImage *pImage)
{
	std::cout << "Saving input image...\n";

	Save::ImageParams params(
		pImage->GetWidth(),
		pImage->GetHeight(),
		pImage->GetBitsPerPixel());

	Save::ImageWriter writer(params, "Images/Cpp_Polarization/input_image.raw");
	writer << pImage->GetData();
}

void processAndSavePolarizedImage(Arena::IImage *pImage, ProcessedPolarizedImage outputImageType)
{
	std::cout << "Processing and saving " << ProcessedPolarizedImageString[outputImageType] << " polarized image..." << std::endl;

	const uint32_t srcWidth = static_cast<uint32_t>(pImage->GetWidth());
	const uint32_t srcHeight = static_cast<uint32_t>(pImage->GetHeight());
	const uint32_t srcPixelFormat = static_cast<uint32_t>(pImage->GetPixelFormat());

	if (srcPixelFormat != static_cast<uint32_t>(PfncFormat::PolarizeMono8) &&
		srcPixelFormat != static_cast<uint32_t>(PfncFormat::PolarizeMono12p) &&
		srcPixelFormat != static_cast<uint32_t>(PfncFormat::PolarizeMono12Packed) &&
		srcPixelFormat != static_cast<uint32_t>(PfncFormat::PolarizeMono16))
	{
		std::cout << "Error - Input image pixel format [" << GetPixelFormatName(static_cast<PfncFormat>(srcPixelFormat)) << "] is a non-polarized format\n";
		return;
	}

	// HSV specific data
	uint8_t* hsvBuffer = nullptr;

	// Deg2x2 specific data
	uint32_t dstHeightCounter = 0;
	uint32_t dstWidthCounter = 0;

	// This is a dummy buffer which is temporarily used to allocate the Arena Image to hold the final processed image
	uint8_t *dummyBuffer = new uint8_t[srcWidth * srcHeight]; // Largest output image size
	Arena::IImage *outputImage = nullptr;

	switch (outputImageType)
	{
		// 1/4 resolution, 3 bytes/pixel
	case ProcessedPolarizedImage::AoLP:
		outputImage = Arena::ImageFactory::Create(dummyBuffer, (srcWidth / 2) * (srcHeight / 2) * 3, srcWidth / 2, srcHeight / 2, PfncFormat::RGB8);
		break;
		// 1/4 resolution, 1 byte/pixel
	case ProcessedPolarizedImage::DoLP:
		outputImage = Arena::ImageFactory::Create(dummyBuffer, (srcWidth / 2) * (srcHeight / 2), srcWidth / 2, srcHeight / 2, PfncFormat::Mono8);
		break;
		// 1/4 resolution, 3 bytes/pixel
	case ProcessedPolarizedImage::HSV:
		outputImage = Arena::ImageFactory::Create(dummyBuffer, (srcWidth / 2) * (srcHeight / 2) * 3, srcWidth / 2, srcHeight / 2, PfncFormat::RGB8);

		// 1/4 resolution, 3 bytes/pixel (H, S, V)
		hsvBuffer = new uint8_t[(srcWidth / 2) * (srcHeight / 2) * 3];
		break;
		// Full resolution, 1 byte/pixel
	case ProcessedPolarizedImage::Deg2x2:
		outputImage = Arena::ImageFactory::Create(dummyBuffer, srcWidth * srcHeight, srcWidth, srcHeight, PfncFormat::Mono8);
		break;
	default:
		delete[] dummyBuffer;
		std::cout << "Error - Cannot process image. Unsupported output image type [" << outputImageType << "]" << std::endl;
		return;
	}

	// Deleting temp buffer used for image creation
	delete[] dummyBuffer;

	// Calibration values
	double factor_0deg = 1.0269;
	double factor_45deg = 1.0;
	double factor_90deg = 1.0385;
	double factor_135deg = 1.005;

	double s0 = 0.0;
	double s1 = 0.0;
	double s2 = 0.0;

	double angle_rad = 0.0;
	double angle_deg = 0.0;

	double dop = 0.0;

	uint8_t *inputBufferPtr = const_cast<uint8_t*>(pImage->GetData());
	uint8_t *outputBuffer = const_cast<uint8_t*>(outputImage->GetData());

	uint16_t x0y0 = 0;
	uint16_t x0y1 = 0;
	uint16_t x1y0 = 0;
	uint16_t x1y1 = 0;

	double polPixel = 0.0;
	double dopPixel = 0.0;

	const double scale_factor = 180.0 / 255.0; // Using max of 180 degrees

	uint32_t outputBufferIndex = 0;

	unsigned char* srcPtr = inputBufferPtr;

	// Process the image taking 4 pixels (0, 45, 90 & 135) at a time
	for (uint32_t y = 0; y < srcHeight; y += 2)
	{
		srcPtr = inputBufferPtr + ((srcWidth * 3 / 2) * y);

		for (uint32_t x = 0; x < srcWidth; x += 2)
		{
			if (srcPixelFormat == PfncFormat::PolarizeMono8)
			{
				x0y0 = inputBufferPtr[(y * srcWidth) + x];
				x0y1 = inputBufferPtr[((y + 1) * srcWidth) + x];
				x1y0 = inputBufferPtr[(y * srcWidth) + x + 1];
				x1y1 = inputBufferPtr[((y + 1) * srcWidth) + x + 1];
			}
			else if (srcPixelFormat == PfncFormat::PolarizeMono16)
			{
				x0y0 = reinterpret_cast<uint16_t*>(inputBufferPtr)[(y * srcWidth) + x];
				x0y1 = reinterpret_cast<uint16_t*>(inputBufferPtr)[((y + 1) * srcWidth) + x];
				x1y0 = reinterpret_cast<uint16_t*>(inputBufferPtr)[(y * srcWidth) + x + 1];
				x1y1 = reinterpret_cast<uint16_t*>(inputBufferPtr)[((y + 1) * srcWidth) + x + 1];
			}
			else if (srcPixelFormat == PfncFormat::PolarizeMono12p)
			{
				x0y0 = ((*(srcPtr + 1) & 0x0F) << 8) | *srcPtr;
				x1y0 = (*(srcPtr + 2) << 4) | (*(srcPtr + 1) >> 4);
				x0y1 = ((*(srcPtr + (srcWidth * 3 / 2) + 1) & 0x0F) << 8) | (*(srcPtr + (srcWidth * 3 / 2)));
				x1y1 = (*(srcPtr + (srcWidth * 3 / 2) + 2) << 4) | (*(srcPtr + (srcWidth * 3 / 2) + 1) >> 4);

				srcPtr += 3;
			}
			else if (srcPixelFormat == PfncFormat::PolarizeMono12Packed)
			{
				x0y0 = (static_cast<uint16_t>(*srcPtr) << 4) | (static_cast<uint16_t>(*(srcPtr + 1)) & 0x0F);
				x1y0 = (static_cast<uint16_t>(*(srcPtr + 2)) << 4) | (static_cast<uint16_t>(*(srcPtr + 1)) >> 4);
				x0y1 = (static_cast<uint16_t>(*(srcPtr + (srcWidth * 3 / 2))) << 4) | (static_cast<uint16_t>(*(srcPtr + (srcWidth * 3 / 2) + 1)) & 0x0F);
				x1y1 = (static_cast<uint16_t>(*(srcPtr + (srcWidth * 3 / 2) + 2)) << 4) | (static_cast<uint16_t>(*(srcPtr + (srcWidth * 3 / 2) + 1)) >> 4);

				srcPtr += 3;
			}

			// At this point we have the current group of 4 pixels
			s0 = max((factor_0deg * x1y1) + (factor_90deg * x0y0), (factor_45deg * x1y0) + (factor_135deg * x0y1));
			s1 = (factor_0deg * x1y1) - (factor_90deg * x0y0);
			s2 = (factor_45deg * x1y0) - (factor_135deg * x0y1);

			if (outputImageType == ProcessedPolarizedImage::AoLP || outputImageType == ProcessedPolarizedImage::HSV)
			{
				angle_rad = 0.5 * atan2(s2, s1);

				if (angle_rad < 0)
				{
					angle_deg = (180 / M_PI) * (angle_rad + M_PI);
				}
				else
				{
					angle_deg = (180 / M_PI) * angle_rad;
				}

				polPixel = angle_deg;
			}

			if (outputImageType == ProcessedPolarizedImage::DoLP || outputImageType == ProcessedPolarizedImage::HSV)
			{
				dop = sqrt(pow(s1, 2) + pow(s2, 2)) / (s0 + 0.001);
				dopPixel = dop * 255.0; // Map 0-1 to 0-255
			}

			// Calculations for the current pixel are complete so now we assign the current pixel value to the output buffer
			if (outputImageType == ProcessedPolarizedImage::AoLP)
			{
				// RGB will be stored in memory in BGR order
				outputBuffer[outputBufferIndex++] = (polar_color_table[static_cast<uint8_t>(polPixel / scale_factor)]) & 0xFF;
				outputBuffer[outputBufferIndex++] = (polar_color_table[static_cast<uint8_t>(polPixel / scale_factor)] >> 8) & 0xFF;
				outputBuffer[outputBufferIndex++] = polar_color_table[static_cast<uint8_t>(polPixel / scale_factor)] >> 16;
			}
			else if (outputImageType == ProcessedPolarizedImage::DoLP)
			{
				outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(dopPixel);
			}
			else if (outputImageType == ProcessedPolarizedImage::HSV)
			{
				// Convert HSV to RGB. See: https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
				// RGB will be stored in memory in BGR order
				double h = polPixel * 2.0;			// Hue
				double s = dopPixel / 255.0;		// Saturation
				double v = 255.0;					// Value

				double c = v * s;
				double h_ = h / 60.0;
				double x = c * (1 - abs(fmod(h_, 2.0) - 1));

				if ((h_ >= 0) && (h_ <= 1))
				{
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(x + v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v);
				}
				else if ((h_ >= 1) && (h_ <= 2))
				{
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(x + v - c);
				}
				else if ((h_ >= 2) && (h_ <= 3))
				{
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(x + v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v - c);
				}
				else if ((h_ >= 3) && (h_ <= 4))
				{
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(x + v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v - c);
				}
				else if ((h_ >= 4) && (h_ <= 5))
				{
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(x + v - c);
				}
				else if ((h_ >= 5) && (h_ < 6))
				{
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(x + v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v - c);
					outputBuffer[outputBufferIndex++] = static_cast<uint8_t>(v);
				}
				else
				{
					outputBuffer[outputBufferIndex++] = 0;
					outputBuffer[outputBufferIndex++] = 0;
					outputBuffer[outputBufferIndex++] = 0;
				}
			}
			else if (outputImageType == ProcessedPolarizedImage::Deg2x2)
			{
				if (srcPixelFormat == PfncFormat::PolarizeMono16)
				{
					x0y0 >>= 8;
					x1y0 >>= 8;
					x0y1 >>= 8;
					x1y1 >>= 8;
				}
				else if (srcPixelFormat == PfncFormat::PolarizeMono12p || srcPixelFormat == PfncFormat::PolarizeMono12Packed)
				{
					x0y0 >>= 4;
					x1y0 >>= 4;
					x0y1 >>= 4;
					x1y1 >>= 4;
				}

				// Output image:
				//   -------------
				//   |  90 |  45 |
				//   |-----------|
				//   | 135 |   0 |
				//   -------------
				outputBuffer[(dstHeightCounter * srcWidth) + dstWidthCounter] = static_cast<uint8_t>(x0y0);
				outputBuffer[(dstHeightCounter * srcWidth) + (srcWidth / 2) + dstWidthCounter] = static_cast<uint8_t>(x1y0);
				outputBuffer[((srcHeight / 2) * srcWidth) + (dstHeightCounter * srcWidth) + (srcWidth / 2) + dstWidthCounter] = static_cast<uint8_t>(x1y1);
				outputBuffer[((srcHeight / 2) * srcWidth) + (dstHeightCounter * srcWidth) + dstWidthCounter] = static_cast<uint8_t>(x0y1);

				dstWidthCounter++;

				if (dstWidthCounter >= (srcWidth / 2))
				{
					dstHeightCounter++;
					dstWidthCounter = 0;
				}
			}
		}
	}

	// Save image
	std::string filename;
	switch (outputImageType)
	{
	case ProcessedPolarizedImage::AoLP:
	{
		std::cout << "Saving colorized Angle of Linear Polarization image\n";
		filename = "Images/Cpp_Polarization/AoLP.png";
		break;
	}
	case ProcessedPolarizedImage::DoLP:
	{
		std::cout << "Saving mono Degree of Linear Polarization image\n";
		filename = "Images/Cpp_Polarization/DoLP.png";
		break;
	}
	case ProcessedPolarizedImage::HSV:
	{
		std::cout << "Saving RGB HSV Polarization image\n";
		filename = "Images/Cpp_Polarization/HSV.png";

		delete[] hsvBuffer;
		break;
	}
	case ProcessedPolarizedImage::Deg2x2:
		std::cout << "Saving Raw 2x2 Individual Angle image\n";
		filename = "Images/Cpp_Polarization/2x2Deg.png";
		break;
	default:
		std::cout << "Error - Cannot save processed image. Unsupported output image type [" << outputImageType << "]" << std::endl;
		Arena::ImageFactory::Destroy(outputImage);
		return;
	}

	Save::ImageParams params(outputImage->GetWidth(), outputImage->GetHeight(), outputImage->GetBitsPerPixel());

	Save::ImageWriter writer(params, filename.c_str());
	writer << outputImage->GetData();

	Arena::ImageFactory::Destroy(outputImage);
}

// Demonstrates acquisition and processing of polarized image data.
// (1) configures the camera to a polarized pixel format
// (2) acquires a polarized input image
// (3) processes the raw input image to Angle of Linear Polarization (AoLP) and
//     maps it to a custom color LUT
// (4) processes the raw input image to Degree of Linear Polarization (DoLP)
// (5) produces a 4-panel image consisting of the data from each filter
//     element (the 0, 90, 45 & 135 degree filters)
// (6) processes the raw input image to an HSV image and saves it as RGB
// A total of 5 images will be saved to disk:
// Raw captured image, AoLP, DoLP, HSV, and the 4 separate filter element image
void AcquireAndProcessPolarizedImage(Arena::IDevice* pDevice)
{
	// get node values that will be changed in order to return their values
	// at the end of the example
	GenICam::gcstring pixelFormatInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "PixelFormat");

	// Set pixel format
	std::cout << TAB1 << "Set pixel format to 'PolarizeMono8'\n";

	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "PixelFormat", "PolarizeMono8");

	// Start stream
	std::cout << TAB1 << "Start stream\n";

	pDevice->StartStream();

	std::cout << TAB2 << "Get one image.\n";

	Arena::IImage* pImage = pDevice->GetImage(TIMEOUT);

	saveRAWInputImage(pImage);

	processAndSavePolarizedImage(pImage, ProcessedPolarizedImage::AoLP);

	processAndSavePolarizedImage(pImage, ProcessedPolarizedImage::DoLP);

	processAndSavePolarizedImage(pImage, ProcessedPolarizedImage::HSV);

	processAndSavePolarizedImage(pImage, ProcessedPolarizedImage::Deg2x2);

	// Re-queue the image buffer
	pDevice->RequeueBuffer(pImage);

	// Stop stream
	std::cout << TAB1 << "Stop stream\n";

	pDevice->StopStream();

	// return nodes to their initial values
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "PixelFormat", pixelFormatInitial);
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

int main()
{
	std::cout << "Cpp_Polarization\n";

	try
	{
		// prepare example
		Arena::ISystem* pSystem = Arena::OpenSystem();

		pSystem->UpdateDevices(100);

		std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();

		if (deviceInfos.size() == 0)
		{
			std::cout << "\nNo camera(s) connected\n";
			return 0;
		}

		Arena::IDevice* pDevice = pSystem->CreateDevice(deviceInfos[0]);

		// run example
		std::cout << "Commence example\n\n";
		AcquireAndProcessPolarizedImage(pDevice);
		std::cout << "\nExample complete\n";

		// clean up example
		pSystem->DestroyDevice(pDevice);
		Arena::CloseSystem(pSystem);
	}
	catch (GenICam::GenericException& ge)
	{
		std::cout << "\nGenICam exception thrown: " << ge.what() << "\n";
		return -1;
	}
	catch (std::exception& ex)
	{
		std::cout << "\nStandard exception thrown: " << ex.what() << "\n";
		return -1;
	}
	catch (...)
	{
		std::cout << "\nUnexpected exception thrown\n";
		return -1;
	}

	std::cout << "Press any key to complete\n";
	std::getchar();
	return 0;
}
