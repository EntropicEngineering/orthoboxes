//
// Created by Benjamin Riggs on 8/23/17.
//

#ifndef _WEBUSB_H
#define _WEBUSB_H

#include <LUFA/Drivers/USB/USB.h>

/** \brief WebUSB Descriptor (LUFA naming conventions).
 *
 *  Type define for a WebUSB Platform Capability Descriptor. This structure uses LUFA-specific element names
 *  to make each element's purpose clearer.
 *
 *  \note Regardless of CPU architecture, these values should be stored as little endian.
 */
typedef struct
{
	USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

	uint8_t  DeviceCapability; /**< Type of the capability: \ref USB_DeviceCapabilityTypes_t DCTYPE_Platform */
	uint8_t  Reserved; /**< This field is reserved and shall be set to zero. */
	uint8_t  PlatformUUID[16]; /**< This is a 128-bit number that uniquely identifies a platform
										   *   specific capability of the device.
										   */
	uint16_t Version; /**< Binary Coded Decimal version of protocol, currently 1.0.0 */
	uint8_t  VendorCode; /**< Value in the bRequest field made by WebUSB Device Requests from browser. */
	uint8_t  LandingPage; /**< Index of the WebUSB Descriptor for the a landing page appropriate to the device. */
} ATTR_PACKED WebUSB_Descriptor_t;

enum WebUSB_Request_t
{
	WebUSB_RTYPE_GetURL = 2, /**< Indicates the device should return the indicated WebUSB_URL descriptor. */
	WebUSB_RTYPE_GetSerialization = 3, /**< Indicates that the device should return the WebUSB HID serialization. */
};

enum WebUSB_Descriptor_t
{
	WebUSB_DTYPE_URL = 2, /**< Indicates that the descriptor is a URL descriptor. */
};

/** \brief WebUSB URL Descriptor (LUFA naming convention).
 *
 *  Type define for a WebUSB URL Descriptor. This structure uses LUFA-specific element names
 *  to make each element's purpose clearer.
 *
 *  \note Regardless of CPU architecture, these values should be stored as little endian.
 */
typedef struct
{
	USB_Descriptor_Header_t Header; /**< Descriptor header, including type (WebUSB_DTYPE_URL) and size. */

	uint8_t Scheme; /**< URL scheme prefix: 0 means http://, 1 means https://, 255 means included in URL */
	char URL[]; /**< UTF-8 encoded URL (excluding scheme prefix). */
};

#endif //_WEBUSB_H
