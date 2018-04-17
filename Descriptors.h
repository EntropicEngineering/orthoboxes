/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "webusb.h"

		#include "MS_OS_20_Device.h"

		#include "debug.h"

		#include "Config/AppConfig.h"

		#include "SimpleHID.h"

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;

			/* HID Interface */
			USB_Descriptor_Interface_t            HID_Interface;
//			USB_HID_Descriptor_HID_t              HID_GenericHID;
			USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;

		/** Type define for the Microsoft OS 2.0 Descriptor for the device. This must be defined in the
		 *  application code as the descriptor may contain sub-descriptors which can vary between devices,
		 *  and which identify which USB drivers Windows should use.
		 */
		typedef struct
		{
			MS_OS_20_Descriptor_Set_Header_t        Header;
			MS_OS_20_CompatibleID_Descriptor        CompatibleID;
			MS_OS_20_Registry_Property_Descriptor   RegistryData;
		} MS_OS_20_Descriptor_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_GenericHID = 0, /**< GenericHID interface descriptor ID */
		};

		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 *  have a unique ID index associated with it, which can be used to refer to the string from
		 *  other descriptors.
		 */
		enum StringDescriptors_t
		{
			STRING_ID_Language          = 0, /**< Supported Languages string descriptor ID (must be zero) */
			STRING_ID_Manufacturer      = 1, /**< Manufacturer string ID */
			STRING_ID_Product           = 2, /**< Product string ID */
			STRING_ID_Serial_Number     = 3,
			STRING_ID_timestamp         = 4,
			STRING_ID_status            = 5,
			STRING_ID_config            = 6,
			STRING_ID_timeout           = 7,
			STRING_ID_error_threshold   = 8,
			STRING_ID_item_order        = 9,
			STRING_ID_wall_error        = 10,
			STRING_ID_duration          = 11,
			STRING_ID_drop_error        = 12,
			STRING_ID_poke              = 13,
			STRING_ID_location          = 14,
			STRING_ID_peg               = 15,
			STRING_ID_new_state         = 16,
			STRING_ID_tool              = 17,
			STRING_ID_event             = 18,
			STRING_ID_event_number      = 19,
			STRING_ID_box_type          = 20,
			STRING_ID_toggle_raw        = 21,
			STRING_ID_raw_values        = 22,
			STRING_ID_hardware_fault    = 23,
			STRING_ID_peg_thresholds    = 24,
			STRING_ID_bootloader        = 255,
		};

		enum {
			HID_REPORTID_TestReport = 0x01,
		} HID_Report_IDs;
	/* Macros: */
		/** Endpoint address of the Generic HID reporting IN endpoint. */
		#define GENERIC_IN_EPADDR         (ENDPOINT_DIR_IN | 1)

		/** Size in bytes of the Generic HID reporting endpoint. */
		#define GENERIC_EPSIZE            8

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

