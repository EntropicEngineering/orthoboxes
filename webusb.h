//
// Created by Benjamin Riggs on 8/23/17.
//

#ifndef _WEBUSB_H
#define _WEBUSB_H

#include <LUFA/Drivers/USB/USB.h>

#define WEBUSB_VERSION VERSION_BCD(1, 0, 0)

#define WEBUSB_REQUEST_TYPE (REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQREC_DEVICE)

#define WEBUSB_PLATFORM_DESCRIPTOR_SIZE 24

/* $ python -c "import uuid;print(', '.join(map(hex, uuid.UUID('3408b638-09a9-47a0-8bfd-a0768815b665').bytes_le)))" */
#define WEBUSB_PLATFORM_UUID 0x38, 0xb6, 0x8, 0x34, 0xa9, 0x9, 0xa0, 0x47, 0x8b, 0xfd, 0xa0, 0x76, 0x88, 0x15, 0xb6, 0x65

/** \brief Convenience macro to easily create \ref USB_Descriptor_DeviceCapability_Platform_t instances for the WebUSB platform.
 *
 * 	\param[in] VendorCode  Vendor Code that all control requests coming from the browser must use.
 *
 * 	\param[in] LandingPageIndex  Index of the URL Descriptor to use as the Landing Page for the device.
 *
 */
#define WEBUSB_DESCRIPTOR(VendorCode, LandingPageIndex) \
	WEBUSB_PLATFORM_DESCRIPTOR_SIZE, DTYPE_DeviceCapability,\
	DCTYPE_Platform, \
	/* Reserved */ 0, \
	WEBUSB_PLATFORM_UUID, \
	(uint8_t)(WEBUSB_VERSION % 256), (uint8_t)(WEBUSB_VERSION / 256), \
	VendorCode, \
	LandingPageIndex

/** \brief Convenience macro to easily create \ref WebUSB_URL_Descriptor_t instances from a wide character string.
 *
 *  \note This macro is for little-endian systems only.
 *
 * 	\param[in] Prefix  0 for "http://", 1 for "https://", 255 for included in the URL string.
 *
 *  \param[in] URL  URL string to initialize a URL Descriptor structure with.
 *
 * 	\note Prefix String literal with u8 to ensure proper conversion: e.g. WEBUSB_URL_DESCRIPTOR(u8"www.google.com")
 */
#define WEBUSB_URL_DESCRIPTOR(Prefix, URL)     { .Header = {.Size = sizeof(WebUSB_URL_Descriptor_t) + (sizeof(URL) - 1), \
															   .Type = WebUSB_DTYPE_URL}, \
													.Scheme = Prefix, .UTF8_URL = URL }

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
	uint8_t UTF8_URL[]; /**< UTF-8 encoded URL (excluding scheme prefix). */
} ATTR_PACKED WebUSB_URL_Descriptor_t;

#endif //_WEBUSB_H
