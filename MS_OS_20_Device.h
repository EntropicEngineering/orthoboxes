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

#ifndef _MS_OS_20_WEBUSB_DEVICE_H
#define _MS_OS_20_WEBUSB_DEVICE_H

	/* Macros */
		#ifndef LONG_TO_BYTES_LE
		#define LONG_TO_BYTES_LE(n) n % 256, (n / 256) % 256, (n / 65536) % 256, (n / 16777216) % 256
		#endif

		/* $ python -c "import uuid;print(', '.join(map(hex, uuid.UUID('D8DD60DF-4589-4CC7-9CD2-659D9E648A9F').bytes_le)))" */
		#define MS_OS_20_PLATFORM_UUID 0xdf, 0x60, 0xdd, 0xd8, 0x89, 0x45, 0xc7, 0x4c, 0x9c, 0xd2, 0x65, 0x9d, 0x9e, 0x64, 0x8a, 0x9f

		#define MS_OS_20_WINDOWS_VERSION CPU_TO_LE32(0x06030000) // Windows version (8.1)

		#define MS_OS_20_ALTERNATE_ENUMERATION_CODE 0 /**< Set to non-zero to enable Windows to allow device to return alternate USB descriptors. */

		/** \brief Convenience macro to easily create device capability platform descriptors for the MS OS 2.0 platform.
		 *
		 *  \note This macro is designed to be wrapped in parentheses and included in a sequence to the \ref BOS_DESCRIPTOR macro.
		 *
		 * 	\param[in] VendorCode  Vendor Code that all control requests coming from Windows must use.
		 */
		#define MS_OS_20_PLATFORM_DESCRIPTOR(VendorCode, TotalLength) \
			/* Total size of this descriptor */ 28, \
			DTYPE_DeviceCapability,\
			DCTYPE_Platform, \
			/* Reserved */ 0, \
			MS_OS_20_PLATFORM_UUID, \
			LONG_TO_BYTES_LE(MS_OS_20_WINDOWS_VERSION), \
			TotalLength , \
			VendorCode, \
			MS_OS_20_ALTERNATE_ENUMERATION_CODE

	/* MS OS 2.0 Descriptors Data Structures */
		enum MS_OS_20_wIndex_t
		{
			MS_OS_20_DESCRIPTOR_INDEX = 0x07, /**< Indicates the device should return MS OS 2.0 Descriptor Set. */
			MS_OS_20_SET_ALT_ENUMERATION = 0x08, /**< Indicates the device may "subsequently return alternate USB descriptors when Windows requests the information." */
		};

		enum MS_OS_20_Descriptor_Types
		{
			MS_OS_20_SET_HEADER_DESCRIPTOR = 0x00,
//			MS_OS_20_SUBSET_HEADER_CONFIGURATION = 0x01,
//			MS_OS_20_SUBSET_HEADER_FUNCTION = 0x02,
			MS_OS_20_FEATURE_COMPATBLE_ID = 0x03,
//			MS_OS_20_FEATURE_REG_PROPERTY = 0x04,
//			MS_OS_20_FEATURE_MIN_RESUME_TIME = 0x05,
//			MS_OS_20_FEATURE_MODEL_ID = 0x06,
//			MS_OS_20_FEATURE_CCGP_DEVICE =0x07,
		};

		/** \brief Microsoft OS 2.0 Descriptor Set Header (LUFA naming convention).
		 *
		 *  \note Regardless of CPU architecture, these values should be stored as little endian.
		 */
		typedef struct {
			uint16_t Length; /**< The length, in bytes, of this header. Shall be set to 10. */
			uint16_t DescriptorType; /**< Shall be set to MS_OS_20_SET_HEADER_DESCRIPTOR */
			uint32_t WindowsVersion;
			uint16_t TotalLength; /**< The size of entire MS OS 2.0 descriptor set. The value shall match the value in the descriptor set information structure. */
		} ATTR_PACKED MS_OS_20_Descriptor_Set_Header_t;

		/** \brief Microsoft OS 2.0 Feature Descriptor for CompatibleID.
		 *
		 *  These values are used by Windows to locate the appropriate driver for the device.
		 *
		 *  For WebUSB in Chrome, the CompatibleID needs to be WINUSB, and the SubCompatibleID is null.
		 *
		 *  \note ID values must be 8 bytes long and contain only the ASCII values for uppercase letters, numbers, underscores, and the NULL character. No other characters are allowed, and the last byte in the ID must be the NULL 0x00.
		 */
		typedef struct {
			uint16_t Length; /**< The length, bytes, of the compatible ID descriptor including value descriptors. Shall be set to 20. */
			uint16_t DescriptorType; /**< MS_OS_20_FEATURE_COMPATIBLE_ID */
			uint8_t CompatibleID[8]; /**< Compatible ID ASCII String */
			uint8_t SubCompatibleID[8]; /**< Sub-compatible ID ASCII String */
		} ATTR_PACKED MS_OS_20_CompatibleID_Descriptor;

#endif //_MS_OS_20_WEBUSB_DEVICE_H
