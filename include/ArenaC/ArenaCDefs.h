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
#pragma once

#include <stdint.h>

#if (defined _WIN32 || defined _WIN64)
#ifdef AC_EXPORTS
#define AC_API __declspec(dllexport)
#else
#define AC_API __declspec(dllimport)
#endif // AC_EXPORTS
#else
#define AC_API __attribute__((visibility("default")))
//		#define AC_API
#endif // _WIN32

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef acSystem;
 *
 * Representation of the system object, the entry point into Arena SDK.
 */
typedef void* acSystem;

/**
 * @typedef acDevice;
 *
 * Represents a device, used to configure and stream a device.
 */
typedef void* acDevice;

/**
 * @typedef acBuffer;
 *
 * Represents a buffer, which carries a payload of either an image or a chunk
 * data. A buffer can hold image data and/or chunk data.
 */
typedef void* acBuffer;

/**
 * @typedef acFeatureStream;
 *
 * Represents a feature stream object, allowing node map configurations to be
 * streamed to and from files.
 */
typedef void* acFeatureStream;

/**
 * @typedef acNodeMap;
 *
 * Represents a node map, or feature tree.
 */
typedef void* acNodeMap;

/**
 * @typedef acNode;
 *
 * Represents a node, or feature.
 */
typedef void* acNode;

/**
 * @typedef acCallback;
 *
 * Represents a callback handle, used to deregister callbacks when they are no
 * longer needed.
 */
typedef void* acCallback;

#ifndef GC_TLI_CLIENT_H_
#if defined(__cplusplus)
typedef bool bool8_t;
#else
typedef uint8_t bool8_t;
#endif
#endif

/**
 * @typedef acCallbackFunction
 *
 * The signature of a function needed to register a callback. An example of a
 * function that could work might look something like the following.
 *
 * \code{.c}
 * 	// a function with the appropriate function signature to register as a callback
 * 	// error handling skipped for brevity
 * 	{
 * 		void onCallback(acNode hNode, void* pUserData)
 * 		{
 * 			UserDataStruct* userData = reinterpret_cast<UserDataStruct*>(pUserData);
 * 			
 * 			char pBuf[100];
 * 			size_t len = 100;
 * 			acNodeGetName(hNode, pBuf, &len);
 * 			// ...
 * 		}
 * 	}
 * \endcode
 */
typedef void (*acCallbackFunction)(acNode, void*);

/**
 * @enum AC_ERROR_LIST
 *
 * This enum represents the different errors that a function might return.
 *
 * @warning 
 *  - Use AC_ERROR integer values in place of AC_ERROR_LIST enum values
 */
enum AC_ERROR_LIST
{
	AC_ERR_SUCCESS = 0,                /*!< Success, no error */
	AC_ERR_ERROR = -1001,              /*!< Generic error */
	AC_ERR_NOT_INITIALIZED = -1002,    /*!< Arena SDK not initialized */
	AC_ERR_NOT_IMPLEMENTED = -1003,    /*!< Function not implemented */
	AC_ERR_RESOURCE_IN_USE = -1004,    /*!< Resource already in use */
	AC_ERR_ACCESS_DENIED = -1005,      /*!< Incorrect access */
	AC_ERR_INVALID_HANDLE = -1006,     /*!< Null/incorrect handle */
	AC_ERR_INVALID_ID = -1007,         /*!< Incorrect ID */
	AC_ERR_NO_DATA = -1008,            /*!< No data available */
	AC_ERR_INVALID_PARAMETER = -1009,  /*!< Null/incorrect parameter */
	AC_ERR_IO = -1010,                 /*!< Input/output error */
	AC_ERR_TIMEOUT = -1011,            /*!< Timed out */
	AC_ERR_ABORT = -1012,              /*!< Function aborted */
	AC_ERR_INVALID_BUFFER = -1013,     /*!< Invalid buffer */
	AC_ERR_NOT_AVAILABLE = -1014,      /*!< Function not available */
	AC_ERR_INVALID_ADDRESS = -1015,    /*!< Invalid register address */
	AC_ERR_BUFFER_TOO_SMALL = -1016,   /*!< Buffer too small */
	AC_ERR_INVALID_INDEX = -1017,      /*!< Invalid index */
	AC_ERR_PARSING_CHUNK_DATA = -1018, /*!< Error parsing chunk data */
	AC_ERR_INVALID_VALUE = -1019,      /*!< Invalid value */
	AC_ERR_RESOURCE_EXHAUSTED = -1020, /*!< Resource cannot perform more actions */
	AC_ERR_OUT_OF_MEMORY = -1021,      /*!< Not enough memory */
	AC_ERR_BUSY = -1022,               /*!< Busy on anothe process */
	AC_ERR_CUSTOM = -10000             /*!< Start adding custom error LIST here */
};

/**
 * @typedef AC_ERROR;
 *
 * Integer representation of the the error enum (AC_ERROR_LIST).
 */
typedef int32_t AC_ERROR;

/**
 * @enum AC_ACCESS_MODE_LIST
 *
 * This enum represents the different access modes for a device or its
 * features.
 *
 * @warning 
 *  - Use AC_ACCESS_MODE integer values in place of AC_ACCESS_MODE_LIST enum
 *    values
 */
enum AC_ACCESS_MODE_LIST
{
	AC_ACCESS_MODE_NI = 0,        /*!< Not implemented */
	AC_ACCESS_MODE_NA = 1,        /*!< Not available */
	AC_ACCESS_MODE_WO = 2,        /*!< Write only */
	AC_ACCESS_MODE_RO = 3,        /*!< Read only */
	AC_ACCESS_MODE_RW = 4,        /*!< Read and write */
	AC_ACCESS_MODE_UNDEFINED = 5, /*!< Undefined */
};

/**
 * @typedef AC_ACCESS_MODE;
 *
 * Integer representation of the access mode enum (AC_ACCESS_MODE_LIST).
 */
typedef int32_t AC_ACCESS_MODE;

/**
 * @enum AC_CACHING_MODE_LIST
 *
 * This enum represents the different caching modes a node might use.
 *
 * @warning 
 *  - Use AC_CACHING_MODE integer values in place of AC_CACHING_MODE_LIST enum
 *    values
 */
enum AC_CACHING_MODE_LIST
{
	AC_CACHING_MODE_NO_CACHE = 0,      /*!< Do not use cache */
	AC_CACHING_MODE_WRITE_THROUGH = 1, /*!< Write to cache and register */
	AC_CACHING_MODE_WRITE_AROUND = 2,  /*!< Write to register, write to cache on read */
	AC_CACHING_MODE_UNDEFINED = 3,     /*!< Undefined */
};

/**
 * @typedef AC_CACHING_MODE;
 *
 * Integer representation of the caching mode enum (AC_CACHING_MODE_LIST).
 */
typedef int32_t AC_CACHING_MODE;

/**
 * @enum AC_NAMESPACE_LIST
 *
 * This enum represents whether a node is in the standard or custom namespaces.
 *
 * @warning 
 *  - Use AC_NAMESPACE integer values in place of AC_NAMESPACE_LIST enum values
 */
enum AC_NAMESPACE_LIST
{
	AC_NAMESPACE_CUSTOM = 0,    /*!< Name resides in custom namespace */
	AC_NAMESPACE_STANDARD = 1,  /*!< Name resides in one of the standard namespaces */
	AC_NAMESPACE_UNDEFINED = 2, /*!< Undefined */
};

/**
 * @typedef AC_NAMESPACE;
 *
 * Integer representation of the namespace enum (AC_NAMESPACE_LIST).
 */
typedef int32_t AC_NAMESPACE;

/**
 * @enum AC_INTERFACE_TYPE_LIST
 *
 * This enum represents the interface type of a node.
 *
 * @warning 
 *  - Use AC_INTERFACE_TYPE integer values in place of AC_INTERFACE_LIST enum
 *    values
 */
enum AC_INTERFACE_TYPE_LIST
{
	AC_INTERFACE_TYPE_VALUE = 0,       /*!< IValue interface */
	AC_INTERFACE_TYPE_BASE = 1,        /*!< IBase interface */
	AC_INTERFACE_TYPE_INTEGER = 2,     /*!< IInteger interface */
	AC_INTERFACE_TYPE_BOOLEAN = 3,     /*!< IBoolean interface */
	AC_INTERFACE_TYPE_COMMAND = 4,     /*!< ICommand interface */
	AC_INTERFACE_TYPE_FLOAT = 5,       /*!< IFloat interface */
	AC_INTERFACE_TYPE_STRING = 6,      /*!< IString interface */
	AC_INTERFACE_TYPE_REGISTER = 7,    /*!< IRegister interface */
	AC_INTERFACE_TYPE_CATEGORY = 8,    /*!< ICategory interface */
	AC_INTERFACE_TYPE_ENUMERATION = 9, /*!< IEnumeration interface */
	AC_INTERFACE_TYPE_ENUMENTRY = 10,  /*!< IEnumEntry interface */
	AC_INTERFACE_TYPE_PORT = 11,       /*!< IPort interface */
};

/**
 * @typedef AC_INTERFACE_TYPE;
 *
 * Integer representation of the interface type enum (AC_INTERFACE_TYPE_LIST).
 */
typedef int32_t AC_INTERFACE_TYPE;

/**
 * @enum AC_VISIBILITY_LIST
 *
 * This enum represents the different visibilities of a node.
 *
 * @warning 
 *  - Use AC_VISIBILITY integer values in place of AC_VISIBILITY_LIST enum
 *    values
 */
enum AC_VISIBILITY_LIST
{
	AC_VISIBILITY_BEGINNER = 0,   /*!< Always visible */
	AC_VISIBILITY_EXPERT = 1,     /*!< Visible for experts or gurus */
	AC_VISIBILITY_GURU = 2,       /*!< Visible for gurus */
	AC_VISIBILITY_INVISIBLE = 3,  /*!< Not visible */
	AC_VISIBILITY_UNDEFINED = 99, /*!< Undefined */
};

/**
 * @typedef AC_VISIBILITY;
 *
 * Integer representation of the visibility enum (AC_VISIBILITY_LIST).
 */
typedef int32_t AC_VISIBILITY;

/**
 * @enum AC_INC_MODE_LIST
 *
 * This enum represents the different increment modes of an integer/float node.
 *
 * @warning 
 *  - Use AC_INC_MODE integer values in place of AC_INC_MODE_LIST enum values
 */
enum AC_INC_MODE_LIST
{
	AC_INC_MODE_NONE = 0,  /*!< The feature has no increment */
	AC_INC_MODE_FIXED = 1, /*!< The feature has a fix increment */
	AC_INC_MODE_LIST = 2   /*!< The feature has a list of valid values */
};

/**
 * @typedef AC_INC_MODE;
 *
 * Integer representation of the increment mode enum (AC_INC_MODE_LIST).
 */
typedef int32_t AC_INC_MODE;

/**
 * @enum AC_REPRESENTATION_LIST
 *
 * This enum represents the different representations of an integer/float node.
 *
 * @warning 
 *  - Use AC_REPRESENTATION integer values in place of AC_REPRESENTATION_LIST
 *    enum values
 */
enum AC_REPRESENTATION_LIST
{
	AC_REPRESENTATION_LINEAR = 0,       /*!< Slider with linear behavior */
	AC_REPRESENTATION_LOGARITHMIC = 1,  /*!< Slider with logarithmic behavior */
	AC_REPRESENTATION_BOOLEAN = 2,      /*!< Check box */
	AC_REPRESENTATION_PURE_NUMBER = 3,  /*!< Decimal number in an edit control */
	AC_REPRESENTATION_HEX_NUMBER = 4,   /*!< Hex number in an edit control */
	AC_REPRESENTATION_IPV4_ADDRESS = 5, /*!< IP address */
	AC_REPRESENTATION_MAC_ADDRESS = 6,  /*!< MAC address */
	AC_REPRESENTATION_UNDEFINED = 7, /* Undefined */
};

/**
 * @typedef AC_REPRESENTATION;
 *
 * Integer representation of the numeric representation enum
 * (AC_REPRESENTATION_LIST).
 */
typedef int32_t AC_REPRESENTATION;

/**
 * @enum AC_DISPLAY_NOTATION_LIST
 *
 * This enum represents the best way to display a float node.
 *
 * @warning 
 *  - Use AC_DISPLAY_NOTATION integer values in place of
 *    AC_DISPLAY_NOTATION_LIST enum values
 */
enum AC_DISPLAY_NOTATION_LIST
{
	AC_DISPLAY_NOTATION_AUTOMATIC = 0,  /*!< The notation if either scientific or fixed depending on what is shorter */
	AC_DISPLAY_NOTATION_FIXED = 1,      /*!< The notation is fixed, e.g. 123.4 */
	AC_DISPLAY_NOTATION_SCIENTIFIC = 2, /*!< The notation is scientific, e.g. 1.234e2 */
	AC_DISPLAY_NOTATION_UNDEFINED = 3,  /*!< Undefined */
};

/**
 * @typedef AC_DISPLAY_NOTATION;
 *
 * Integer representation of the display notation enum
 * (AC_DISPLAY_NOTATION_LIST).
 */
typedef int32_t AC_DISPLAY_NOTATION;

/**
 * @enum AC_PAYLOAD_TYPE_LIST
 *
 * This enum represents the different payload types of a buffer.
 *
 * @warning 
 *  - Use AC_PAYLOAD_TYPE integer values in place of AC_PAYLOAD_LIST enum
 *    values
 */
enum AC_PAYLOAD_TYPE_LIST
{
	AC_PAYLOAD_TYPE_IMAGE = 0x0001,                /*!< Image data only */
	AC_PAYLOAD_TYPE_IMAGE_EXTENDED_CHUNK = 0x4001, /*!< Image data extended with chunk data */
	AC_PAYLOAD_TYPE_CHUNKDATA = 0x0004             /*!< Chunk data only; image data may be present as chunk */
};

/**
 * @typedef AC_PAYLOAD_TYPE;
 *
 * Integer representation of the payload type enum (AC_PAYLOAD_TYPE_LIST).
 */
typedef int32_t AC_PAYLOAD_TYPE;

/**
 * @enum AC_PIXEL_ENDIANNESS_LIST
 *
 * This enum represents the different pixel endiannesses.
 *
 * @warning 
 *  - Use AC_PIXEL_ENDIANNESS integer values in place of
 *    AC_PIXEL_ENDIANNESS_LIST enum values
 */
enum AC_PIXEL_ENDIANNESS_LIST
{
	AC_PIXEL_ENDIANNESS_UNKNOWN = 0, /*!< Unknown pixel endianness */
	AC_PIXEL_ENDIANNESS_LITTLE = 1,  /*!< Little endian */
	AC_PIXEL_ENDIANNESS_BIG = 2      /*!< Big endian */
};

/**
 * @typedef AC_PIXEL_ENDIANNESS;
 *
 * Integer representation of the pixel endianness enum
 * (AC_PIXEL_ENDIANNESS_LIST).
 */
typedef int32_t AC_PIXEL_ENDIANNESS;

/**
 * @enum AC_BAYER_ALGORITHM_LIST
 *
 * This enum represents the different algorithms available to interpolate bayer
 * image data.
 *
 * @warning 
 *  - Use AC_BAYER_ALGORITHM integer values in place of AC_BAYER_ALGORITHM_LIST
 *    enum values
 */
enum AC_BAYER_ALGORITHM_LIST
{
	AC_BAYER_ALGORITHM_UNKNOWN = 0,                      /*!< Undefined algorithm */
	AC_BAYER_ALGORITHM_DIRECTIONAL_INTERPOLATION = 1,    /*!< Algorithm that averages nearest neighbours (faster) */
	AC_BAYER_ALGORITHM_ADAPTIVE_HOMOGENEITY_DIRECTED = 2 /*!< Adaptive algorithm that uses directional data (slower, more accurate coloring) */
};

/**
 * @typedef AC_BAYER_ALGORITHM;
 *
 * Integer representation of the bayer algorithm enum
 * (AC_BAYER_ALGORITHM_LIST).
 */
typedef int32_t AC_BAYER_ALGORITHM;

/**
 * @enum AC_START_STREAM_FLAGS_LIST
 *
 * This enum represents the transport layer flags for starting a stream.
 */
enum AC_START_STREAM_FLAGS_LIST
{
	AC_START_STREAM_FLAG_DEFAULT = 1,       /*!< default behaviour for the underlying transport layer */
	AC_START_STREAM_FLAG_GVSP_LEGACY = 1001 /*!< Will try to start Gvsp 2.0 stream with 16bit block id if supported */
};

/**
 * @typedef AC_START_STREAM_FLAGS;
 *
 * Integer representation of the start stream flags
 * (AC_START_STREAM_FLAGS_LIST).
 */
typedef int32_t AC_START_STREAM_FLAGS;

#ifdef __cplusplus
} // extern "C"
#endif
