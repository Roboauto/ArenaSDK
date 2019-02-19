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
#include "ArenaCApi.h"
#include "SaveCApi.h"

#define TAB1 "  "

// Save: Introduction
//    This example introduces the basic save capabilities of the save library.
//    It shows the construction of an image parameters object and an image
//    writer, and saves a single image.

// =-=-=-=-=-=-=-=-=-
// =-=- SETTINGS =-=-
// =-=-=-=-=-=-=-=-=-

// Pixel format
//    Windows and Linux operating systems have different preferred pixel
//    formats for displaying images. BGR8 is a good choice for Windows, RGB8
//    for Linux.
#if defined _WIN32
#define PIXEL_FORMAT 0x02180015 // BGR8
#elif defined linux
#define PIXEL_FORMAT 0x02180014 //RGB8
#endif

// File name
//    The relative path and file name to save to. After running the example,
//    the an image should exist at the location specified. The image writer
//    chooses the file format by the image's extension. Aside from PNG (.png),
//    images can be saved as JPEG (.jpg), TIFF (.tiff), BMP (.bmp), and raw
//    (.raw) files.
#define FILE_NAME "Images/C_Save_Images/image.png"

// =-=-=-=-=-=-=-=-=-
// =-=- EXAMPLE -=-=-
// =-=-=-=-=-=-=-=-=-

// demonstrates saving an image
// (1) converts image to a displayable pixel format
// (2) prepares image parameters
// (3) prepares image writer
// (4) saves image
// (5) destroys converted image
AC_ERROR SaveImage(acBuffer hBuffer)
{
	// AC_ERROR and SC_ERROR values are equivalent
	AC_ERROR acErr = AC_ERR_SUCCESS;
	SC_ERROR saveErr = SC_ERR_SUCCESS;

	// Convert image
	//    Convert the image to a displayable pixel format. It is worth keeping in
	//    mind the best pixel and file formats for your application. This example
	//    converts the image so that its displayable by the operating system.
	printf("%sConvert image to %s\n", TAB1, (PIXEL_FORMAT == 0x02180015 ? "BGR8" : "RGB8"));
	acBuffer hConverted = NULL;

	acErr = acImageFactoryConvert(hBuffer, PIXEL_FORMAT, &hConverted);
	if (acErr != AC_ERR_SUCCESS)
		return acErr;

	// Prepare image parameters
	//    An image's width, height, and bits per pixel are required to save to
	//    disk.
	printf("%sPrepare image parameters\n", TAB1);

	// get width
	size_t width = 0;

	acImageGetWidth(hConverted, &width);
	if (acErr != AC_ERR_SUCCESS)
		return acErr;

	// get height
	size_t height = 0;

	acImageGetHeight(hConverted, &height);
	if (acErr != AC_ERR_SUCCESS)
		return acErr;

	// get bits per pixel
	size_t bpp = 0;

	acImageGetBitsPerPixel(hConverted, &bpp);
	if (acErr != AC_ERR_SUCCESS)
		return acErr;

	// Prepare image writer
	//    The image writer requires the image's parameters, a specified file name
	//    or pattern, and the image data to save. Providing these should result in
	//    a successfully saved file on the disk. Because an image's parameters and
	//    file name pattern may repeat, they can be passed into the image writer's
	//    constructor.
	printf("%sPrepare image writer\n", TAB1);
	saveWriter hWriter = NULL;

	saveErr = saveWriterCreate(width, height, bpp, &hWriter);
	if (saveErr != SC_ERR_SUCCESS)
		return saveErr;

	saveErr = saveWriterSetFileNamePattern(hWriter, FILE_NAME);
	if (saveErr != SC_ERR_SUCCESS)
		return saveErr;

	// Save image
	//    Get and save the image. Notice that pointers to the beginning of the
	//    image data stay valid for the life cycle of the object, and do not
	//    require memory allocation or object destruction.
	printf("%sSave image\n", TAB1);

	// get image
	uint8_t* pData = NULL;

	acErr = acImageGetData(hConverted, &pData);
	if (acErr != AC_ERR_SUCCESS)
		return acErr;

	// save image
	saveErr = saveWriterSave(hWriter, pData);
	if (saveErr != SC_ERR_SUCCESS)
		return saveErr;

	// destroy image writer
	saveErr = saveWriterDestroy(hWriter);
	if (saveErr != SC_ERR_SUCCESS)
		return saveErr;

	// destroy converted image
	acErr = acImageFactoryDestroy(hConverted);
	return acErr;
}

// =-=-=-=-=-=-=-=-=-
// =- PREPARATION -=-
// =- & CLEAN UP =-=-
// =-=-=-=-=-=-=-=-=-

#define CHECK_RETURN                                      \
	if (err != AC_ERR_SUCCESS)                            \
	{                                                     \
		printf("Error: %d\n\nExample completed.\n", err); \
		return -1;                                        \
	}

int main()
{
	printf("C_Save\n");
	AC_ERROR err = AC_ERR_SUCCESS;

	// prepare example
	acSystem hSystem = NULL;
	err = acOpenSystem(&hSystem);
	CHECK_RETURN;
	err = acSystemUpdateDevices(hSystem, 100);
	CHECK_RETURN;
	size_t numDevices = 0;
	err = acSystemGetNumDevices(hSystem, &numDevices);
	CHECK_RETURN;
	if (numDevices == 0)
	{
		printf("Error: no devices connected, example requires at least one device\n");
		return 0;
	}
	acDevice hDevice = NULL;
	err = acSystemCreateDevice(hSystem, 0, &hDevice);
	CHECK_RETURN;
	err = acDeviceStartStream(hDevice);
	CHECK_RETURN;
	acBuffer hBuffer = NULL;
	err = acDeviceGetBuffer(hDevice, 2000, &hBuffer);
	CHECK_RETURN;

	// run example
	printf("Commence example\n\n");
	err = SaveImage(hBuffer);
	CHECK_RETURN;
	printf("\nExample complete\n");

	// clean up example
	err = acDeviceRequeueBuffer(hDevice, hBuffer);
	CHECK_RETURN;
	err = acDeviceStopStream(hDevice);
	CHECK_RETURN;
	err = acSystemDestroyDevice(hSystem, hDevice);
	CHECK_RETURN;
	err = acCloseSystem(hSystem);
	CHECK_RETURN;

	printf("Press any key to complete\n");
	getchar();
	return 0;
}
