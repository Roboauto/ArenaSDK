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

#define TAB1 "  "
#define TAB2 "    "

// Save: File Name Pattern
//    This example demonstrates saving a set of images according to a file name
//    pattern, which uses the <count> and <timestamp> tags to differentiate
//    between saved images. The essential points of the example include setting
//    the image writer up with a file name pattern and using the cascading I/O
//    operator (<<) to update the timestamp and save each image. 

// =-=-=-=-=-=-=-=-=-
// =-=- SETTINGS =-=-
// =-=-=-=-=-=-=-=-=-

// File name pattern
//    The relative path and file name pattern to save to. File name patterns
//    can be used with the <count> and <timestamp> tags to save files according
//    to a pattern. The <count> tag is replaced by an internal counter that is
//    automatically updated on each save. The <timestamp> tag, however, must be
//    updated manually for each image. Aside from BMP (.bmp), images can be
//    saved as JPEG (.jpg), TIFF (.tiff), PNG (.png), and raw (.raw) files. 
#define FILE_NAME_PATTERN "Images/Cpp_Save_FileNamePattern/image<count>-<timestamp>.bmp"

// number of images to acquire and save
#define NUM_IMAGES 25

// image timeout (milliseconds)
#define TIMEOUT 2000

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

// demonstrates saving images using a pattern
// (1) prepares image parameters
// (2) prepares image writer with a file name pattern, including <count> and <timestamp> tags
// (3) starts stream and grabs images
// (4) saves images each image without supplying new file names
// (5) requeues buffers and stops stream
void AcquireAndSaveImages(Arena::IDevice* pDevice)
{
	// get width, height, and pixel format nodes
	GenApi::CIntegerPtr pWidth = pDevice->GetNodeMap()->GetNode("Width");
	GenApi::CIntegerPtr pHeight = pDevice->GetNodeMap()->GetNode("Height");
	GenApi::CEnumerationPtr pPixelFormat = pDevice->GetNodeMap()->GetNode("PixelFormat");

	if (!pWidth || !pHeight || !pPixelFormat)
	{
		throw GenICam::GenericException("Width, Height, or PixelFormat node could not be found", __FILE__, __LINE__);
	}

	if (!GenApi::IsReadable(pWidth) || !GenApi::IsReadable(pHeight) || !GenApi::IsReadable(pPixelFormat))
	{
		throw GenICam::GenericException("Width, Height, or PixelFormat node not readable", __FILE__, __LINE__);
	}

	// Prepare image parameters from device settings
	//    An image's width, height, and bits per pixel are required to save to
	//    disk. Its size and stride (i.e. pitch) can be calculated from those 3
	//    inputs. Notice that an image's size and stride use bytes as a unit whiel
	//    the bits per pixel uses bits. Arena defines its pixel formats by the
	//    PFNC (Pixel Format Naming Convention), which embeds the number of bits
	//    per pixel within a pixel format's integer representation. 
	std::cout << TAB1 << "Prepare image parameters\n";

	Save::ImageParams params(
		static_cast<size_t>(pWidth->GetValue()),
		static_cast<size_t>(pHeight->GetValue()),
		Arena::GetBitsPerPixel(pPixelFormat->GetCurrentEntry()->GetValue()));

	// Prepare image writer
	//    The image writer requires 3 arguments to save an image: the iamge's
	//    parameters, a specified file name or pattern, and the iamge data to
	//    save. If a file name pattern uses the <timestamp> tag, then a timestamp
	//    must also be provided. Providing these should result in a successfully
	//    saved file on the disk. Because an image's parameters and file name
	//    pattern may repeat, they can be passed into the image writer's
	//    constructor. However, they can also be passed in dynamically using the
	//    cascading I/O operator (<<). 
	std::cout << TAB1 << "Prepare image writer\n";

	Save::ImageWriter writer(
		params,
		FILE_NAME_PATTERN);

	// start stream
	std::cout << TAB1 << "Start stream\n";

	pDevice->StartStream();

	// get images
	std::cout << TAB1 << "Get " << NUM_IMAGES << " images\n";

	for (int i = 0; i < NUM_IMAGES; i++)
	{
		std::cout << TAB2 << "Save image " << i;

		// get image
		Arena::IImage* pImage = pDevice->GetImage(TIMEOUT);

		// Update timestamp and save image
		//    Timestamps can easily be added to a file name or path by using the
		//    <timestamp> tag within the file name pattern. Using the timestamp tag
		//    requires the timestamp to be updated before each save. The << operator
		//    easily allows for this type of dynamic updating. 
		writer << pImage->GetTimestampNs() << pImage->GetData();

		// Get last file name
		//    The image writer allows for the retrieval of paths, file names, and
		//    extensions. They can be retrieved together or separately, and it is
		//    possible to get the pattern, peek ahead at the next file name, or get
		//    the last file name. 
		std::cout << " at " << writer.GetLastFileName(true) << "\n";

		// reque image buffer
		pDevice->RequeueBuffer(pImage);
	}

	// stop stream
	std::cout << "Stop stream\n";

	pDevice->StopStream();
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

// Example preparation & clean up
//    Prepares the example by opening the system, creating a device, and
//    configuring it. Cleans up the example by destroying the device and
//    closing the system. 
int main()
{
	std::cout << "Cpp_Save_FileNamePattern\n";

	try
	{
		// prepare example
		Arena::ISystem* pSystem = Arena::OpenSystem();
		pSystem->UpdateDevices(100);
		std::vector<Arena::DeviceInfo> devices = pSystem->GetDevices();
		if (devices.size() == 0)
		{
			std::cout << "\nNo camera(s) connected\n";
			return 0;
		}
		Arena::IDevice* pDevice = pSystem->CreateDevice(devices[0]);

		// run example
		std::cout << "Commence example\n\n";
		AcquireAndSaveImages(pDevice);
		std::cout << "\nExample complete." << std::endl;

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
