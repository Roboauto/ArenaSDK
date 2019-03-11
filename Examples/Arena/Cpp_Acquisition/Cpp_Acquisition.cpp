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
#define TAB2 "    "

// Acquisition: Introduction
//    This example introduces the basics of image acquisition including
//    acquisition and buffer handling modes, starting and stopping the stream,
//    grabbing and requeuing buffers, and retrieving data on images.

// =-=-=-=-=-=-=-=-=-
// =-=- SETTINGS =-=-
// =-=-=-=-=-=-=-=-=-

// Image timeout
//    Timeout for grabbing images (in milliseconds). If no image is available
//    at the end of the timeout, an exception is thrown. The timeout is the
//    maximum time to wait for an image; however, getting an image will return
//    as soon as an image is available, not waiting the full extent of the
//    timeout.
#define TIMEOUT 2000

// number of images to grab
#define NUM_IMAGES 25

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

// demonstrates acquisition
// (1) sets acquisition mode
// (2) sets buffer handling mode
// (3) starts the stream
// (4) gets a number of images
// (5) prints information from images
// (6) requeues buffers
// (7) stops the stream
void AcquireImages(Arena::IDevice* pDevice)
{
	// get node values that will be changed in order to return their values
	// at the end of the example
	GenICam::gcstring acquisitionModeInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode");

	// Set acquisition mode
	//    Set acquisition mode before starting the stream. Starting the stream
	//    requires the acquisition mode to be set beforehand. The acquisition mode
	//    controls the number of images a device acquires once the stream has been
	//    started. Setting the acquisition mode to 'Continuous' keeps the stream
	//    from stopping. This example returns the camera to its initial
	//    acquisition mode near the end of the example.
	std::cout << TAB1 << "Set acquisition mode to 'Continuous'\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetNodeMap(),
		"AcquisitionMode",
		"Continuous");

	// Set buffer handling mode
	//    Set buffer handling mode before starting the stream. Starting the stream
	//    requires the buffer handling mode to be set beforehand. The buffer
	//    handling mode determines the order and behavior of buffers in the
	//    underlying stream engine. Setting the buffer handling mode to
	//    'NewestOnly' ensures the most recent image is delivered, even if it
	//    means skipping frames.
	std::cout << TAB1 << "Set buffer handling mode to 'NewestOnly'\n";

	Arena::SetNodeValue<GenICam::gcstring>(
		pDevice->GetTLStreamNodeMap(),
		"StreamBufferHandlingMode",
		"NewestOnly");

	// Start stream
	//    Start the stream before grabbing any images. Starting the stream
	//    allocates buffers, which can be passed in as an argument (default: 10),
	//    and begins filling them with data. Starting the stream blocks write
	//    access to many features such as width, height, and pixel format, as well
	//    as acquisition and buffer handling modes, among others. The stream needs
	//    to be stopped later.
	std::cout << TAB1 << "Start stream\n";

	pDevice->StartStream();

	// get images
	std::cout << TAB1 << "Getting " << NUM_IMAGES << " images\n";

	for (int i = 0; i < NUM_IMAGES; i++)
	{
		// Get image
		//    Retrieve images after the stream has started. If the timeout expires
		//    before an image is retrieved, example will throw. Because of this, the
		//    timeout should be at least a bit larger than the exposure time.
		std::cout << TAB2 << "Get image " << i;

		Arena::IImage* pImage = pDevice->GetImage(TIMEOUT);

		// Get image information
		//    Images have information available from them beyond the basics including
		//    information related to data type, image parameters, and error handling.
		size_t size = pImage->GetSizeFilled();
		size_t width = pImage->GetWidth();
		size_t height = pImage->GetHeight();
		GenICam::gcstring pixelFormat = GetPixelFormatName(static_cast<PfncFormat>(pImage->GetPixelFormat()));
		uint64_t timestampNs = pImage->GetTimestampNs();

		std::cout << " (" << size << " bytes; " << width << "x" << height << "; " << pixelFormat << "; timestamp (ns): " << timestampNs << ")";

		// Requeue image buffer
		//    Requeue an image buffer when access to it is no longer needed. Notice
		//    that failing to requeue buffers may cause memory to leak and may also
		//    result in the stream engine being starved due to there being no
		//    available buffers.
		std::cout << " and requeue\n";

		pDevice->RequeueBuffer(pImage);
	}

	// Stop stream
	//    Stop the stream after all images have been requeued. Failing to stop the
	//    stream will leak memory.
	std::cout << TAB1 << "Stop stream\n";

	pDevice->StopStream();

	// return nodes to their initial values
	Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode", acquisitionModeInitial);
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

int main()
{
	// flag to track when an exception has been thrown
	bool exceptionThrown = false;

	std::cout << "Cpp_Acquisition\n";

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
		AcquireImages(pDevice);
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
