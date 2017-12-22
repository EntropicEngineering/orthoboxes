/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Benjamin Riggs (https://github.com/riggs)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef _SIMPLE_HID_DEVICE_H
#define _SIMPLE_HID_DEVICE_H

	/* Macros */
		#define SIMPLE_HID_VERSION VERSION_BCD(1, 0, 0)

		#define SIMPLE_HID_PLATFORM_DESCRIPTOR_SIZE 40

		/* $ python -c "import uuid;print(', '.join(map(hex, uuid.UUID('a8adf97c-6a20-48e4-a97c-79978eec00c7').bytes_le)))" */
		#define SIMPLE_HID_PLATFORM_UUID 0x7c, 0xf9, 0xad, 0xa8, 0x20, 0x6a, 0xe4, 0x48, 0xa9, 0x7c, 0x79, 0x97, 0x8e, 0xec, 0x0, 0xc7

		/** \brief Default Usage Page and Usage IDs to designate serialization of report data.
		 *
		 * 	Explanation for values given here: https://github.com/riggs/SimpleHID
		 */
		#ifndef SIMPLE_HID_USAGE_PAGE
		#define SIMPLE_HID_USAGE_PAGE 0xFFAA
		#endif
		#ifndef SIMPLE_HID_APPLICATION_COLLECTION
		#define SIMPLE_HID_APPLICATION_COLLECTION 0x0000
		#endif
		#ifndef SIMPLE_HID_ARRAY
		#define SIMPLE_HID_ARRAY 0x0001
		#endif
		#ifndef SIMPLE_HID_OBJECT
		#define SIMPLE_HID_OBJECT 0x0002
		#endif
		#ifndef SIMPLE_HID_BIT_FIELD
		#define SIMPLE_HID_BIT_FIELD 0x0003
		#endif
		#ifndef SIMPLE_HID_UINT
		#define SIMPLE_HID_UINT 0x0004
		#endif
		#ifndef SIMPLE_HID_INT
		#define SIMPLE_HID_INT 0x0005
		#endif
		#ifndef SIMPLE_HID_FLOAT
		#define SIMPLE_HID_FLOAT 0x0006
		#endif
		#ifndef SIMPLE_HID_UTF8
		#define SIMPLE_HID_UTF8 0x0007
		#endif

		#define BYTES_LE(n) (uint8_t)(n % 256), (uint8_t)(n / 256)

		/** \brief Convenience macro to easily create device capability platform descriptors for the WebUSB-HID platform. This
		 *  macro is designed to be wrapped in parenthese and included in a sequece to the \ref BOS_DESCRIPTOR macro.
		 *
		 * 	\param[in] VendorCode  Vendor Code that all control requests coming from the browser must use.
		 *
		 * 	\param[in] LandingPageIndex  Index of the URL Descriptor to use as the Landing Page for the device.
		 *
		 */
		#define SIMPLE_HID_DESCRIPTOR_CUSTOM(PAGE, COLLECTION, ARRAY, OBJECT, BITS, UINT, INT, FLOAT, UTF8) \
			SIMPLE_HID_PLATFORM_DESCRIPTOR_SIZE, DTYPE_DeviceCapability,\
			DCTYPE_Platform, \
			/* Reserved */ 0, \
			SIMPLE_HID_PLATFORM_UUID, \
			BYTES_LE(SIMPLE_HID_VERSION), \
			BYTES_LE(PAGE), BYTES_LE(COLLECTION), BYTES_LE(ARRAY), BYTES_LE(OBJECT), BYTES_LE(BITS), BYTES_LE(UINT), BYTES_LE(INT), BYTES_LE(FLOAT), BYTES_LE(UTF8)

		#define SIMPLE_HID_DESCRIPTOR_DEFAULT \
			SIMPLE_HID_DESCRIPTOR_CUSTOM( \
				SIMPLE_HID_USAGE_PAGE, \
				SIMPLE_HID_APPLICATION_COLLECTION, \
				SIMPLE_HID_ARRAY, \
				SIMPLE_HID_OBJECT, \
				SIMPLE_HID_BIT_FIELD, \
				SIMPLE_HID_UINT, \
				SIMPLE_HID_INT, \
				SIMPLE_HID_FLOAT, \
				SIMPLE_HID_UTF8 \
			)

#endif //_SIMPLE_HID_DEVICE_H
