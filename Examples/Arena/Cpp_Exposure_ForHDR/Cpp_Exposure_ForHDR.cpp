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

#ifdef __linux__
#define INFINITE 0xFFFFFFFF
#endif

#define TAB1 "  "
#define TAB2 "    "
#define TAB3 "      "

// Exposure: For High Dynamic Range
//    This example demonstrates dynamically updating the exposure time in order
//    to grab images appropriate for high dynamic range (or HDR) imaging. HDR
//    images can be created by combining a number of images acquired at various
//    exposure times. This example demonstrates grabbing three images for this
//    purpose, without the actual creation of an HDR image. 

// =-=-=-=-=-=-=-=-=-
// =-=- SETTINGS =-=-
// =-=-=-=-=-=-=-=-=-

// Exposure times
#define EXPOSURE_HIGH 2500.0
#define EXPOSURE_MID 1000.0
#define EXPOSURE_LOW 500.0

// Image timeout
//    Timeout for grabbing images (in milliseconds). Have the timeout at least
//    a bit larger than the highest exposure time to avoid timing out. 
#define TIMEOUT INFINITE

// number of images to grab
#define NUM_HDR_IMAGES 5

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

// HDR image struct
//    This struct holds the information needed for a single HDR image. This
//    includes one image taken with a high exposure time, one with a medium
//    exposure time, and one with a fairly low exposure time. 
struct HDRImage
{
public:
	Arena::IImage* m_pImageHigh = NULL;
	Arena::IImage* m_pImageMid = NULL;
	Arena::IImage* m_pImageLow = NULL;
};

// demonstrates exposure configuration and acquisition for HDR imaging
// (1) sets trigger mode
// (2) disables automatic exposure
// (3) sets high exposure time
// (4) gets first image
// (5) sets medium exposure time
// (6) gets second image
// (7) sets low exposure time
// (8) gets third images
// (9) copies images into object for later processing
// (10) does NOT process copied images
// (11) cleans up copied images
void AcquireHDRImages(Arena::IDevice* pDevice)
{
	// get node values that will be changed in order to return their values
	// at the end of the example
	GenICam::gcstring triggerModeInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerMode");
	GenICam::gcstring triggerSourceInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSource");
	GenICam::gcstring triggerSelectorInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSelector");
	GenICam::gcstring exposureAutoInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "ExposureAuto");
	double exposureTimeInitial = Arena::GetNodeValue<double>(pDevice->GetNodeMap(), "ExposureTime");

	// Prepare trigger mode
	//    Enable trigger mode before starting the stream. This example uses the
	//    trigger to control the moment that images are taken. This ensures the
	//    exposure time of each image in a way that a continuous stream might have
	//    trouble with. 
	std::cout << TAB1 << "Prepare trigger mode\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"TriggerMode",
		"On");

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"TriggerSource",
		"Software");

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"TriggerSelector",
		"FrameStart");

	// Disable automatic exposure
	//    Disable automatic exposure before starting the stream. The HDR images in
	//    this example require three images of varied exposures, which need to be
	//    set manually. 
	std::cout << TAB1 << "Disable automatic exposure\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"ExposureAuto",
		"Off");

	// Get exposure time and software trigger nodes
	//    The exposure time and software trigger nodes are retrieved beforehand in
	//    order to check for existance, readability, and writability only once
	//    before the stream. 
	std::cout << TAB1 << "Get exposure time and trigger software nodes\n";

	GenApi::CFloatPtr pExposureTime = pDevice->GetNodeMap()->GetNode("ExposureTime");
	GenApi::CCommandPtr pTriggerSoftware = pDevice->GetNodeMap()->GetNode("TriggerSoftware");

	if (!pExposureTime || !pTriggerSoftware)
	{
		throw GenICam::GenericException("ExposureTime or TriggerSoftware node not found", __FILE__, __LINE__);
	}

	if (!GenApi::IsWritable(pExposureTime) || !GenApi::IsWritable(pTriggerSoftware))
	{
		throw GenICam::GenericException("ExposureTime or TriggerSoftware node not writable", __FILE__, __LINE__);
	}

	// start stream
	pDevice->StartStream();

	// get images for HDR
	std::cout << TAB1 << "Acquire HDR images\n";

	std::vector<HDRImage> hdrImages;

	for (int i = 0; i < NUM_HDR_IMAGES; i++)
	{
		// Get high, medium, and low exposure images
		//    This example grabs three examples of varying exposures for later
		//    processing. For each image, the exposure must be set, an image must be
		//    triggered, and then that image must be retrieved. After the exposure
		//    time is changed, the setting does not take place on the device until
		//    after the next frame. Because of this, two images are retrieved, the
		//    first of which is discarded. 
		std::cout << TAB2 << "Get HDR image " << i << "\n";

		// high exposure image
		pExposureTime->SetValue(EXPOSURE_HIGH);
		pTriggerSoftware->Execute();
		Arena::IImage* pImagePreHigh = pDevice->GetImage(TIMEOUT);
		pTriggerSoftware->Execute();
		Arena::IImage* pImageHigh = pDevice->GetImage(TIMEOUT);

		std::cout << TAB3 << "High image (timestamp " << pImageHigh->GetTimestampNs() << ", exposure " << EXPOSURE_HIGH << ")\n";

		// medium exposure image
		pExposureTime->SetValue(EXPOSURE_MID);
		pTriggerSoftware->Execute();
		Arena::IImage* pImagePreMid = pDevice->GetImage(TIMEOUT);
		pTriggerSoftware->Execute();
		Arena::IImage* pImageMid = pDevice->GetImage(TIMEOUT);

		std::cout << TAB3 << "Mid image (timestamp " << pImageMid->GetTimestampNs() << ", exposure " << EXPOSURE_MID << ")\n";

		// low exposure image
		pExposureTime->SetValue(EXPOSURE_LOW);
		pTriggerSoftware->Execute();
		Arena::IImage* pImagePreLow = pDevice->GetImage(TIMEOUT);
		pTriggerSoftware->Execute();
		Arena::IImage* pImageLow = pDevice->GetImage(TIMEOUT);

		std::cout << TAB3 << "Low image (timestamp " << pImageLow->GetTimestampNs() << ", exposure " << EXPOSURE_LOW << ")\n";

		// Copy images for processing later
		//    Use the image factory to copy the images for later processing. Images
		//    are copied in order to requeue buffers to allow for more images to be
		//    retrieved from the device. 
		std::cout << TAB2 << "Copy images for HDR processing later\n";

		HDRImage hdrImage;
		hdrImage.m_pImageHigh = Arena::ImageFactory::Copy(pImageHigh);
		hdrImage.m_pImageMid = Arena::ImageFactory::Copy(pImageMid);
		hdrImage.m_pImageLow = Arena::ImageFactory::Copy(pImageLow);
		hdrImages.push_back(hdrImage);

		// requeue buffers
		pDevice->RequeueBuffer(pImagePreHigh);
		pDevice->RequeueBuffer(pImageHigh);
		pDevice->RequeueBuffer(pImagePreMid);
		pDevice->RequeueBuffer(pImageMid);
		pDevice->RequeueBuffer(pImagePreLow);
		pDevice->RequeueBuffer(pImageLow);
	}

	// stop stream
	pDevice->StopStream();

	// Run HDR processing
	//    Once the images have been retrieved and copied, they can be processed
	//    into an HDR image. HDR algorithms 
	std::cout << TAB1 << "Run HDR processing\n";

	// ...
	// ...
	// ...

	// clean up copied images
	for (size_t i = 0; i < hdrImages.size(); i++)
	{
		Arena::ImageFactory::Destroy(hdrImages[i].m_pImageHigh);
		Arena::ImageFactory::Destroy(hdrImages[i].m_pImageMid);
		Arena::ImageFactory::Destroy(hdrImages[i].m_pImageLow);
	}

	// return nodes to their initial values
	Arena::SetNodeValue<double>(pDevice->GetNodeMap(), "ExposureTime", exposureTimeInitial);
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "ExposureAuto", exposureAutoInitial);
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSelector", triggerSelectorInitial);
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSource", triggerSourceInitial);
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerMode", triggerModeInitial);
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

int main()
{
	// flag to track when an exception has been thrown
	bool exceptionThrown = false;

	std::cout << "Cpp_Exposure_ForHDR\n";

	try
	{
		// prepare example
		Arena::ISystem* pSystem = Arena::OpenSystem();
		pSystem->UpdateDevices(100);
		std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();
		if (deviceInfos.size() == 0)
		{
			std::cout << "\nNo camera connected\nPress enter to complete\n";
			std::getchar();
			return 0;
		}
		Arena::IDevice* pDevice = pSystem->CreateDevice(deviceInfos[0]);

		// run example
		std::cout << "Commence example\n\n";
		AcquireHDRImages(pDevice);
		std::cout << "\nExample complete\n";

		// clean up example
		pSystem->DestroyDevice(pDevice);
		Arena::CloseSystem(pSystem);
	}
	catch (GenICam::GenericException& ge)
	{
		std::cout << "\nGenICam exception thrown: " << ge.what() << "\n";
		exceptionThrown = true;
	}
	catch (std::exception& ex)
	{
		std::cout << "\nStandard exception thrown: " << ex.what() << "\n";
		exceptionThrown = true;
	}
	catch (...)
	{
		std::cout << "\nUnexpected exception thrown\n";
		exceptionThrown = true;
	}

	std::cout << "Press enter to complete\n";
	std::getchar();

	if (exceptionThrown)
		return -1;
	else
		return 0;
}
