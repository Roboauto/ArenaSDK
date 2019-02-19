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

#define TAB1 "  "

// Simple Acquisition
//    This examples demonstrates the most basic code path of acquiring an image
//    using Arena SDK. This includes device enumeration, image acquisition, and
//    clean up. 

// =-=-=-=-=-=-=-=-=-
// =-=- SETTINGS =-=-
// =-=-=-=-=-=-=-=-=-

// timeout for updating the device list
#define UPDATE_TIMEOUT 100

// timeout for grabbing an image
#define IMAGE_TIMEOUT 2000

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

// demonstrates simplest route to acquiring an image
// (1) enumerates device
// (2) acquires image
// (3) cleans up
void EnumerateDeviceAndAcquireImage()
{
	// Enumerate device
	//    Starting Arena just requires opening the system. From there, update and
	//    grab the device list, and create the device. Notice that failing to
	//    update the device list will return an empty list, even if devices are
	//    connected. 
	std::cout << TAB1 << "Enumerate device\n";

	Arena::ISystem* pSystem = Arena::OpenSystem();
	pSystem->UpdateDevices(100);
	std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();

	if (deviceInfos.size() > 0)
	{
		Arena::IDevice* pDevice = pSystem->CreateDevice(deviceInfos[0]);

		// Acquire image
		//    Once a device is created, it is only a single call to acquire an image.
		//    The timeout must be larger than the exposure time. 
		std::cout << TAB1 << "Acquire image\n";

		pDevice->StartStream();
		Arena::IImage* pImage = pDevice->GetImage(IMAGE_TIMEOUT);

		// Clean up
		//    Clean up each of the 3 objects in reverse order: image, device, and
		//    system. The list of devices is a standard vector, so it cleans itself
		//    up at the end of scope. 
		std::cout << TAB1 << "Clean up Arena\n";

		pDevice->RequeueBuffer(pImage);
		pDevice->StopStream();
		pSystem->DestroyDevice(pDevice);
	}

	Arena::CloseSystem(pSystem);
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

int main()
{
	std::cout << "Cpp_SimpleAcquisition\n";

	try
	{
		// run example
		std::cout << "Commence example\n\n";
		EnumerateDeviceAndAcquireImage();
		std::cout << "\nExample complete\n";
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
