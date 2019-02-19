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
#include "GenTL.h"

#ifdef  __linux__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include "GenICam.h"

#ifdef  __linux__
#pragma GCC diagnostic pop
#endif

#include "ArenaApi.h"

#define TAB1 "  "
#define TAB2 "    "
#define TAB3 "      "

// Trigger: Introduction
//    This example introduces basic trigger configuration and use. In order to
//    configure trigger, enable trigger mode and set the source and selector.
//    In order to use it, trigger and retrieve an image. 

// =-=-=-=-=-=-=-=-=-
// =-=- SETTINGS =-=-
// =-=-=-=-=-=-=-=-=-

// image timeout
#define TIMEOUT 2000

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

// demonstrates basic trigger configuration and use
// (1) sets trigger mode, source, and selector
// (2) starts stream
// (3) triggers image
// (4) gets image
// (5) requeues buffer
// (6) stops stream
void ConfigureTriggerAndAcquireImage(Arena::IDevice* pDevice)
{
	// get node values that will be changed in order to return their values
	// at the end of the example
	GenICam::gcstring triggerModeInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode");
	GenICam::gcstring triggerSourceInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSource");
	GenICam::gcstring triggerSelectorInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSelector");

	// Set trigger mode
	//    Enable trigger mode before setting the source and selector and before
	//    starting the stream. Trigger mode cannot be turned on and off while the
	//    device is streaming. 
	std::cout << TAB1 << "Enable trigger mode\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"TriggerMode",
		"On");

	// Set trigger source
	//    Set the trigger source to software in order to trigger images without
	//    the use of any additional hardware. Lines of the GPIO can also be used
	//    to trigger. 
	std::cout << TAB1 << "Set trigger source to Software\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"TriggerSource",
		"Software");

	// Set trigger selector
	//    Set the trigger selector to FrameStart. When triggered, the device will
	//    start acquiring a single frame. This can also be set to AcquisitionStart
	//    or FrameBurstStart. 
	std::cout << TAB1 << "Set trigger selector to FrameStart\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"TriggerSelector",
		"FrameStart");

	// Start stream
	//    When trigger mode is off and the acquisition mode is set to stream
	//    continuously, starting the stream will have the camera begin acquiring a
	//    steady stream of images. However, with trigger mode enabled, the device
	//    will wait for the trigger before acquiring any. 
	std::cout << TAB1 << "Start stream\n";

	pDevice->StartStream();

	// Trigger an image
	//    Trigger an image manually, since trigger mode is enabled. This triggers
	//    the camera to acquire a single image. A buffer is then filled and moved
	//    to the output queue, where it will wait to be retrieved. 
	std::cout << TAB2 << "Trigger image\n";

	Arena::ExecuteNode(
		pDevice->GetNodeMap(),
		"TriggerSoftware");

	// Get image
	//    Once an image has been triggered, it can be retrieved. If no image, has
	//    been triggered, trying to retrieve an image will hang for the duration
	//    of the timeout and then throw an exception. 
	std::cout << TAB2 << "Get image";

	Arena::IImage* pImage = pDevice->GetImage(TIMEOUT);

	std::cout << " (" << pImage->GetWidth() << "x" << pImage->GetHeight() << ")\n";

	// requeue buffer
	std::cout << TAB2 << "Reqeue buffer\n";

	pDevice->RequeueBuffer(pImage);

	// Stop the stream
	std::cout << TAB1 << "Stop stream\n";

	pDevice->StopStream();

	// return nodes to their initial values
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSelector", triggerSelectorInitial);
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "TriggerSource", triggerSourceInitial);
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode", triggerModeInitial);
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

int main()
{
	try
	{
		// prepare example
		Arena::ISystem* pSystem = Arena::OpenSystem();
		pSystem->UpdateDevices(1000);
		std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();
		if (deviceInfos.size() == 0)
		{
			std::cout << "\nNo camera(s) connected\n";
			return 0;
		}
		Arena::IDevice* pDevice = pSystem->CreateDevice(deviceInfos[0]);

		// run example
		std::cout << "Commence example\n\n";
		ConfigureTriggerAndAcquireImage(pDevice);
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
		std::cout << "Standard exception thrown: " << ex.what() << "\n";
		return -1;
	}
	catch (...)
	{
		std::cout << "Unexpected exception thrown\n";
		return -1;
	}

	std::cout << "Press any key to complete\n";
	std::getchar();
	return 0;
}
