/***************************************************************************************
 ***                                                                                 ***
 ***  Copyright (c) 2019, Lucid Vision Labs, Inc.                                    ***
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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @fn SC_ERROR SC_API saveWriterCreateEmpty(saveWriter* phWriter)
 *
 * @param phWriter
 *  - Type: saveWriter*
 *  - [Out] parameter
 *  - Created image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterCreateEmpty </B> creates an empty/default image writer. The
 * parameters of this image writer are not set (height = width = bits per pixel
 * = 0). The default file name pattern is 'savedimages/image<count>.jpg' and
 * the default file format is jpeg.
 *
 * @warning 
 *  - unable to save before setting parameters
 */
SC_ERROR SC_API saveWriterCreateEmpty(saveWriter* phWriter);

/**
 * @fn SC_ERROR SC_API saveWriterCreate(size_t width, size_t height, size_t bitsPerPixel, saveWriter* phWriter)
 *
 * @param width
 *  - Type: size_t
 *  - [In] parameter
 *  - Width of the image(s) to save
 *
 * @param height
 *  - Type: size_t
 *  - [In] parameter
 *  - Height of the image(s) to save
 *
 * @param bitsPerPixel
 *  - Type: size_t
 *  - [In] parameter
 *  - Number of bits per pixel of the image(s) to save
 *
 * @param phWriter
 *  - Type: saveWriter*
 *  - [Out] parameter
 *  - Created image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterCreate </B> creates an image writer while setting the parameters
 * of the upcoming image(s) to save. The default file name pattern is
 * 'savedimages/image<count>.jpg' and the default file format is jpeg.
 */
SC_ERROR SC_API saveWriterCreate(size_t width, size_t height, size_t bitsPerPixel, saveWriter* phWriter);

/**
 * @fn SC_ERROR SC_API saveWriterDestroy(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterDestroy </B> cleans up an image writer (saveWriter),
 * deallocating its memory.
 *
 * @see 
 *  - saveWriter
 */
SC_ERROR SC_API saveWriterDestroy(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetJpeg(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetJpeg </B> changes the image writer to save images using the
 * jpeg file format. It also switches the extension to '.jpg'.
 */
SC_ERROR SC_API saveWriterSetJpeg(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetBmp(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetBmp </B> changes the image writer to save images using the
 * bmp file format. It also switches the extension to '.bmp'.
 */
SC_ERROR SC_API saveWriterSetBmp(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetRaw(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetRaw </B> changes the image writer to save images as raw data.
 * It also switches the extension to '.raw'.
 */
SC_ERROR SC_API saveWriterSetRaw(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetPly(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetPly </B> changes the image writer to save images as ply data.
 * It also switches the extension to '.ply'.
 */
SC_ERROR SC_API saveWriterSetPly(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetTiff(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetTiff </B> changes the image writer to save images using the
 * tiff file format. It also switches the extension to '.tiff'.
 */
SC_ERROR SC_API saveWriterSetTiff(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetPng(saveWriter hWriter)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetPng </B> changes the image writer to save images using the
 * png file format. It also switches the extension to '.png'.
 */
SC_ERROR SC_API saveWriterSetPng(saveWriter hWriter);

/**
 * @fn SC_ERROR SC_API saveWriterSetExtension(saveWriter hWriter, const char* pExtension)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pExtension
 *  - Type: const char*
 *  - [In] parameter
 *  - Extension to use
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetExtension </B> changes the extension of the file format to
 * use. Be aware that changing the extension does not change the file format.
 *
 * @warning 
 *  - does not affect the file format
 */
SC_ERROR SC_API saveWriterSetExtension(saveWriter hWriter, const char* pExtension);

/**
 * @fn SC_ERROR SC_API saveWriterSetParams(saveWriter hWriter, size_t width, size_t height, size_t bitsPerPixel)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param width
 *  - Type: size_t
 *  - [In] parameter
 *  - Width of the image(s) to save
 *
 * @param height
 *  - Type: size_t
 *  - [In] parameter
 *  - Height of the image(s) to save
 *
 * @param bitsPerPixel
 *  - Type: size_t
 *  - [In] parameter
 *  - Bits per pixel of the image(s) to save
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetParams </B> sets the parameters for the image(s) to save.
 */
SC_ERROR SC_API saveWriterSetParams(saveWriter hWriter, size_t width, size_t height, size_t bitsPerPixel);

/**
 * @fn SC_ERROR SC_API saveWriterSetFileNamePattern(saveWriter hWriter, const char* pFileNamePattern)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pFileNamePattern
 *  - Type: const char*
 *  - [In] parameter
 *  - File name pattern to set
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetFileNamePattern </B> sets a new file name or pattern to use
 * to save images. Include '<count>' to include an image count (specific to this
 * image image writer). Include '<timestamp>' to include a timestamp. An image's
 * timestamp must be updated manually.
 */
SC_ERROR SC_API saveWriterSetFileNamePattern(saveWriter hWriter, const char* pFileNamePattern);

/**
 * @fn SC_ERROR SC_API saveWriterUpdateTag(saveWriter hWriter, const char* pTag, const char* pValue)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pTag
 *  - Type: const char*
 *  - [In] parameter
 *  - Tag to replace
 *
 * @param pValue
 *  - Type: const char*
 *  - [In] parameter
 *  - Value to set
 *
 * @return 
 *  - none
 *
 * <B> saveWriterUpdateTag </B> updates the value to replace a given tag when an
 * image is saved.
 */
SC_ERROR SC_API saveWriterUpdateTag(saveWriter hWriter, const char* pTag, const char* pValue);

/**
 * @fn SC_ERROR SC_API saveWriterSetCount(saveWriter hWriter, uint64_t count)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param count
 *  - Type: uint64_t
 *  - [In] parameter
 *  - Count to set
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetCount </B> manually sets the count particular to the image
 * writer. The count increments with each saved image.
 */
SC_ERROR SC_API saveWriterSetCount(saveWriter hWriter, uint64_t count);

/**
 * @fn SC_ERROR SC_API saveWriterSetCountPath(saveWriter hWriter, uint64_t count)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param count
 *  - Type: uint64_t
 *  - [In] parameter
 *  - Count to set
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetCount </B> manually sets the count particular to the file
 * name pattern. The count increments with each saved image.
 */
SC_ERROR SC_API saveWriterSetCountPath(saveWriter hWriter, uint64_t count);

/**
 * @fn SC_ERROR SC_API saveWriterSetCountGlobal(saveWriter hWriter, uint64_t count)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param count
 *  - Type: uint64_t
 *  - [In] parameter
 *  - Count to set
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetCount </B> manually sets the count across all image writers
 * and video recorders. The count increments with each saved image.
 */
SC_ERROR SC_API saveWriterSetCountGlobal(saveWriter hWriter, uint64_t count);

/**
 * @fn SC_ERROR SC_API saveWriterSetTimestamp(saveWriter hWriter, uint64_t timestamp)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param timestamp
 *  - Type: uint64_t
 *  - [In] parameter
 *  - Timestamp to set
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSetTimestamp </B> manually sets the timestamp. The timestamp
 * must be updated manually.
 *
 * @deprecated 
 *  - Deprecated in favor of the more generic tag and value components
 */
SC_ERROR SC_API saveWriterSetTimestamp(saveWriter hWriter, uint64_t timestamp);

/**
 * @fn SC_ERROR SC_API saveWriterGetParams(saveWriter hWriter, size_t* pWidth, size_t* pHeight, size_t* pBitsPerPixel)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pWidth
 *  - Type: size_t*
 *  - [Out] parameter
 *  - Accepts null
 *  - The width
 *
 * @param pHeight
 *  - Type: size_t*
 *  - [Out] parameter
 *  - Accepts null
 *  - The height
 *
 * @param pBitsPerPixel
 *  - Type: size_t*
 *  - [Out] parameter
 *  - Accepts null
 *  - Number of bits per pixel
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterGetParams </B> retrieves the parameters currently used to save
 * images.
 *
 * @warning 
 *  - At least one [Out] parameter must be non-null
 */
SC_ERROR SC_API saveWriterGetParams(saveWriter hWriter, size_t* pWidth, size_t* pHeight, size_t* pBitsPerPixel);

/**
 * @fn SC_ERROR SC_API saveWriterGetFileNamePattern(saveWriter hWriter, char* pFileNamePattern, size_t* pLen)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pFileNamePattern
 *  - Type: char*
 *  - [Out] parameter
 *  - Accepts null
 *  - File name pattern
 *
 * @param pLen
 *  - Type: size_t*
 *  - [In/out] parameter
 *  - (In) Length of the buffer 
 *  - (Out) Length of the value
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterGetFileNamePattern </B> retrieves the file name pattern. The
 * received file name pattern does not replace tags (e.g. <count>, <timestamp>).
 */
SC_ERROR SC_API saveWriterGetFileNamePattern(saveWriter hWriter, char* pFileNamePattern, size_t* pLen);

/**
 * @fn SC_ERROR SC_API saveWriterGetExtension(saveWriter hWriter, char* pExtension, size_t* pLen)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pExtension
 *  - Type: char*
 *  - [Out] parameter
 *  - Accepts null
 *  - Current extension
 *
 * @param pLen
 *  - Type: size_t*
 *  - [In/out] parameter
 *  - (In) Length of the buffer 
 *  - (Out) Length of the value
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterGetExtension </B> retrieves the extension currently being used
 * (e.g. '.jpg', '.png').
 *
 * @warning 
 *  - extension does not necessarily represent its file format
 */
SC_ERROR SC_API saveWriterGetExtension(saveWriter hWriter, char* pExtension, size_t* pLen);

/**
 * @fn SC_ERROR SC_API saveWriterPeekFileName(saveWriter hWriter, char* pFileName, size_t* pLen)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pFileName
 *  - Type: char*
 *  - [Out] parameter
 *  - Accepts null
 *  - Next file name to use
 *
 * @param pLen
 *  - Type: size_t*
 *  - [In/out] parameter
 *  - (In) Length of the buffer 
 *  - (Out) Length of the value
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterPeekFileName </B> peeks at the next file name to use, replacing
 * any appropriate tags (e.g. <count>, <timestamp>).
 */
SC_ERROR SC_API saveWriterPeekFileName(saveWriter hWriter, char* pFileName, size_t* pLen);

/**
 * @fn SC_ERROR SC_API saveWriterPeekCount(saveWriter hWriter, uint64_t* pCount)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pCount
 *  - Type: uint64_t*
 *  - [Out] parameter
 *  - Count
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterPeekCount </B> peeks at the count/index of the next saved image
 * particular to the image writer. This is the number that the <count> or
 * <count:local> tags will be replaced with.
 */
SC_ERROR SC_API saveWriterPeekCount(saveWriter hWriter, uint64_t* pCount);

/**
 * @fn SC_ERROR SC_API saveWriterPeekCountPath(saveWriter hWriter, uint64_t* pCount)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pCount
 *  - Type: uint64_t*
 *  - [Out] parameter
 *  - Path count
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterPeekCount </B> peeks at the count/index of the next saved image
 * particular to the file name pattern. This is the number that the <count:path>
 * tag will be replaced with.
 */
SC_ERROR SC_API saveWriterPeekCountPath(saveWriter hWriter, uint64_t* pCount);

/**
 * @fn SC_ERROR SC_API saveWriterPeekCountGlobal(saveWriter hWriter, uint64_t* pCount)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pCount
 *  - Type: uint64_t*
 *  - [Out] parameter
 *  - Global count
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterPeekCount </B> peeks at the count/index of the next saved image
 * across all image writers and video recorders. This is the number that the
 * <count:global> tag will be replaced with.
 */
SC_ERROR SC_API saveWriterPeekCountGlobal(saveWriter hWriter, uint64_t* pCount);

/**
 * @fn SC_ERROR SC_API saveWriterGetLastFileName(saveWriter hWriter, char* pFileName, size_t* pLen)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pFileName
 *  - Type: char*
 *  - [Out] parameter
 *  - Accepts null
 *  - Last file name used
 *
 * @param pLen
 *  - Type: size_t*
 *  - [In/out] parameter
 *  - (In) Length of the buffer 
 *  - (Out) Length of the value
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterGetLastFileName </B> retrieves the last file name used to save a
 * video with this context. Returns '' if no file has been saved.
 */
SC_ERROR SC_API saveWriterGetLastFileName(saveWriter hWriter, char* pFileName, size_t* pLen);

/**
 * @fn SC_ERROR SC_API saveWriterSave(saveWriter hWriter, const uint8_t* pData)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pData
 *  - Type: const uint8_t*
 *  - [In] parameter
 *  - Image data to save
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSave </B> saves an image starting from the upper leftmost pixel.
 */
SC_ERROR SC_API saveWriterSave(saveWriter hWriter, const uint8_t* pData);

/**
 * @fn SC_ERROR SC_API saveWriterSaveBottomToTop(saveWriter hWriter, const uint8_t* pData)
 *
 * @param hWriter
 *  - Type: saveWriter
 *  - [In] parameter
 *  - An image writer
 *
 * @param pData
 *  - Type: const uint8_t*
 *  - [In] parameter
 *  - Image data to save
 *
 * @return 
 *  - Type: SC_ERROR
 *  - Error code for the function
 *  - Returns SC_ERR_SUCCESS (0) on success
 *
 * <B> saveWriterSaveBottomToTop </B> saves an image starting from the lower
 * leftmost pixel.
 */
SC_ERROR SC_API saveWriterSaveBottomToTop(saveWriter hWriter, const uint8_t* pData);

#ifdef __cplusplus
}
#endif
