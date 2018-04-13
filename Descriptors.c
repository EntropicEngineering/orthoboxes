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
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"
#include "Timer.h"
#include "led.h"
#include "box.h"

#define USAGE(id) HID_RI_USAGE(8, id)
#define STRING_INDEX(i) HID_RI_STRING(8, i)
#define REPORT_COLLECTION HID_RI_COLLECTION(8, 0x03)
#define END_COLLECTION HID_RI_END_COLLECTION(0)
#define REPORT_ID(id) HID_RI_REPORT_ID(8, id)
#define REPORT_COUNT(c) HID_RI_REPORT_COUNT(8, c)
#define REPORT_SIZE(s) HID_RI_REPORT_SIZE(8, s)

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM HID_Descriptor_Pokey[] =
{
		HID_RI_USAGE_PAGE(16, SIMPLE_HID_USAGE_PAGE),
		HID_RI_USAGE(0, SIMPLE_HID_APPLICATION_COLLECTION), /* Can be size 0 because value is 0 */
		HID_RI_COLLECTION(8, 0x01), /* Application Collection */

		/* Report Name: 'config'
		 * Report ID:   1
		 * Report Type: Feature
		 * Report Data: { 'timeout': Uint32,
		 *                'error_threshold': Uint16,
		 *                'item_order': Uint8[10] }
		 */
		STRING_INDEX(STRING_ID_config),
		REPORT_ID(1),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timeout),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(32), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_error_threshold),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(16), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_item_order),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(10), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: 'timestamp'
		 * Report ID:   1
		 * Report Type: Output
		 * Report Data: [ Uint64 ]
		 */
		STRING_INDEX(STRING_ID_timestamp),
		REPORT_ID(1),
		USAGE(SIMPLE_HID_ARRAY), /* Technically redundant because Array is default */
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_OUTPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: 'status'
		 * Report ID:   1
		 * Report Type: Input
		 * Report Data: { 'timestamp': Uint64,
		 *                'status': Uint8[4] }
		 */
		STRING_INDEX(STRING_ID_status),
		REPORT_ID(1),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_status),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(4), REPORT_COUNT(4), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: 'wall_error'
		 * Report ID:   12
		 * Report Type: Input
		 * Report Data: { 'timestamp': Uint64,
		 *                'duration': Uint32 }
		 */
		STRING_INDEX(STRING_ID_wall_error),
		REPORT_ID(12),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_duration),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(32), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: drop_error
		 * Report ID:   13
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64 }
		 */
		STRING_INDEX(STRING_ID_drop_error),
		REPORT_ID(13),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: poke
		 * Report ID:   14
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                location: Uint8 }
		 */
		STRING_INDEX(STRING_ID_poke),
		REPORT_ID(14),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_location),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: peg
		 * Report ID:   15
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                location: Uint8,
		 *                new_state: Uint8 }
		 */
		STRING_INDEX(STRING_ID_peg),
		REPORT_ID(15),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_location),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_new_state),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: tool
		 * Report ID:   16
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                new_state: Uint8 }
		 */
		STRING_INDEX(STRING_ID_tool),
		REPORT_ID(16),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_new_state),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Debug Reports */
		/* Report Name: event
		 * Report ID:   17
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                event_number: Uint8 }
		 */
		STRING_INDEX(STRING_ID_event),
		REPORT_ID(17),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_event_number),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: box_type
		 * Report ID:   0x45
		 * Report Type: Feature
		 * Report Data: { box_type: Uint8 }
		 */
		STRING_INDEX(STRING_ID_box_type),
		REPORT_ID(0x45),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_box_type),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: toggle_raw
		 * Report ID:   0x45
		 * Report Type: Output
		 * Report Data: None
		 */
		REPORT_ID(0x45),
		STRING_INDEX(STRING_ID_toggle_raw),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			REPORT_SIZE(0), REPORT_COUNT(1), HID_RI_OUTPUT(0),
		END_COLLECTION,

		/* Report Name: raw_values
		 * Report ID:   0x45
		 * Report Type: Input
		 * Report Data: [ ...Uint16[10], ...Uint8[10] ]
		 */
		STRING_INDEX(STRING_ID_raw_values),
		REPORT_ID(0x45),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(16), REPORT_COUNT(10), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(10), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: hardware_fault
		 * Report ID:   70
		 * Report Type: Feature
		 * Report Data: [ Uint64 ]
		 */
		STRING_INDEX(STRING_ID_hardware_fault),
		REPORT_ID(70),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: peg_thresholds
		 * Report ID:   71
		 * Report Type: Feature
		 * Report Data: [ ...Uint16[6] ]
		 */
		STRING_INDEX(STRING_ID_peg_thresholds),
		REPORT_ID(71),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(16), REPORT_COUNT(6), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Set Feature to this report triggers bootloader */
		/* Report Name: bootloader
		 * Report ID:   0xFF
		 * Report Type: Feature (Set only)
		 * Report Data: None
		 */
		STRING_INDEX(STRING_ID_bootloader),
		REPORT_ID(START_BOOTLOADER_REPORT_ID),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			REPORT_SIZE(0), REPORT_COUNT(1), HID_RI_FEATURE(0),
		END_COLLECTION,

	HID_RI_END_COLLECTION(0),
};

const USB_Descriptor_HIDReport_Datatype_t PROGMEM HID_Descriptor_Peggy[] =
{
	HID_RI_USAGE_PAGE(16, SIMPLE_HID_USAGE_PAGE),
	HID_RI_USAGE(0, SIMPLE_HID_APPLICATION_COLLECTION), /* Can be size 0 because value is 0 */
	HID_RI_COLLECTION(8, 0x01), /* Application Collection */

		/* Report Name: 'config'
		 * Report ID:   1
		 * Report Type: Feature
		 * Report Data: { 'timeout': Uint32,
		 *                'error_threshold': Uint16 }
		 */
		STRING_INDEX(STRING_ID_config),
		REPORT_ID(1),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timeout),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(32), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_error_threshold),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(16), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: 'timestamp'
		 * Report ID:   1
		 * Report Type: Output
		 * Report Data: [ Uint64 ]
		 */
		STRING_INDEX(STRING_ID_timestamp),
		REPORT_ID(1),
		USAGE(SIMPLE_HID_ARRAY), /* Technically redundant because Array is default */
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_OUTPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: 'status'
		 * Report ID:   1
		 * Report Type: Input
		 * Report Data: { 'timestamp': Uint64,
		 *                'status': Uint8[4] }
		 */
		STRING_INDEX(STRING_ID_status),
		REPORT_ID(1),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_status),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(4), REPORT_COUNT(4), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: 'wall_error'
		 * Report ID:   12
		 * Report Type: Input
		 * Report Data: { 'timestamp': Uint64,
		 *                'duration': Uint32 }
		 */
		STRING_INDEX(STRING_ID_wall_error),
		REPORT_ID(12),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_duration),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(32), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

	    /* Report Name: drop_error
		 * Report ID:   13
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64 }
		 */
		STRING_INDEX(STRING_ID_drop_error),
		REPORT_ID(13),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: poke
		 * Report ID:   14
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                location: Uint8 }
		 */
		STRING_INDEX(STRING_ID_poke),
		REPORT_ID(14),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_location),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: peg
		 * Report ID:   15
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                location: Uint8,
		 *                new_state: Uint8 }
		 */
		STRING_INDEX(STRING_ID_peg),
		REPORT_ID(15),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_location),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_new_state),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: tool
		 * Report ID:   16
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                new_state: Uint8 }
		 */
		STRING_INDEX(STRING_ID_tool),
		REPORT_ID(16),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_new_state),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Debug Reports */
		/* Report Name: event
		 * Report ID:   17
		 * Report Type: Input
		 * Report Data: { timestamp: Uint64,
		 *                event_number: Uint8 }
		 */
		STRING_INDEX(STRING_ID_event),
		REPORT_ID(17),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_timestamp),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			STRING_INDEX(STRING_ID_event_number),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: box_type
		 * Report ID:   0x45
		 * Report Type: Feature
		 * Report Data: { box_type: Uint8 }
		 */
		STRING_INDEX(STRING_ID_box_type),
		REPORT_ID(0x45),
		USAGE(SIMPLE_HID_OBJECT),
		REPORT_COLLECTION,
			STRING_INDEX(STRING_ID_box_type),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: toggle_raw
		 * Report ID:   0x45
		 * Report Type: Output
		 * Report Data: None
		 */
		REPORT_ID(0x45),
		STRING_INDEX(STRING_ID_toggle_raw),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			REPORT_SIZE(0), REPORT_COUNT(1), HID_RI_OUTPUT(0),
		END_COLLECTION,

		/* Report Name: raw_values
		 * Report ID:   0x45
		 * Report Type: Input
		 * Report Data: [ ...Uint16[10], ...Uint8[10] ]
		 */
		STRING_INDEX(STRING_ID_raw_values),
		REPORT_ID(0x45),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(16), REPORT_COUNT(10), HID_RI_INPUT(8, HID_IOF_VARIABLE),
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(8), REPORT_COUNT(10), HID_RI_INPUT(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: hardware_fault
		 * Report ID:   70
		 * Report Type: Feature
		 * Report Data: [ Uint64 ]
		 */
		STRING_INDEX(STRING_ID_hardware_fault),
		REPORT_ID(70),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(64), REPORT_COUNT(1), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Report Name: peg_thresholds
		 * Report ID:   71
		 * Report Type: Feature
		 * Report Data: [ ...Uint16[6] ]
		 */
		STRING_INDEX(STRING_ID_peg_thresholds),
		REPORT_ID(71),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			USAGE(SIMPLE_HID_UINT), REPORT_SIZE(16), REPORT_COUNT(6), HID_RI_FEATURE(8, HID_IOF_VARIABLE),
		END_COLLECTION,

		/* Set Feature to this report triggers bootloader */
		/* Report Name: bootloader
		 * Report ID:   0xFF
		 * Report Type: Feature (Set only)
		 * Report Data: None
		 */
		STRING_INDEX(STRING_ID_bootloader),
		REPORT_ID(START_BOOTLOADER_REPORT_ID),
		USAGE(SIMPLE_HID_ARRAY),
		REPORT_COLLECTION,
			REPORT_SIZE(0), REPORT_COUNT(1), HID_RI_FEATURE(0),
		END_COLLECTION,

	HID_RI_END_COLLECTION(0),
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(2,0,1),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 1209,
	.ProductID              = 2801,
	.ReleaseNumber          = VERSION_BCD(0,1,1),

	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = STRING_ID_Serial_Number,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

//NOTE: THIS IS BAD. DO NOT ALLOW THIS TO PERSIST
const USB_Descriptor_Device_t PROGMEM DeviceDescriptorPokey =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(2,0,1),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 1209,
	.ProductID              = 2800,
	.ReleaseNumber          = VERSION_BCD(0,1,1),

	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Binary device Object Store (BOS) descriptor structure. This descriptor, located in FLASH memory, describes a
 *  flexible and extensible framework for describing and adding device-level capabilities to the set of USB standard
 *  specifications. The BOS descriptor defines a root descriptor that is similar to the configuration descriptor,
 *  and is the base descriptor for accessing a family of related descriptors. It defines the number of 'sub' Device
 *  Capability Descriptors and the total length of itself and the sub-descriptors.
 */

const USB_Descriptor_BOS_t PROGMEM BOSDescriptor = BOS_DESCRIPTOR(
	(MS_OS_20_PLATFORM_DESCRIPTOR(MS_OS_20_VENDOR_CODE, MS_OS_20_DESCRIPTOR_SET_TOTAL_LENGTH))
	(WEBUSB_DESCRIPTOR(WEBUSB_VENDOR_CODE, WEBUSB_LANDING_PAGE_INDEX))
	(SIMPLE_HID_DESCRIPTOR_DEFAULT)
);

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = STRING_ID_Product,

			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.HID_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = INTERFACE_ID_GenericHID,
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

//			.Class                  = HID_CSCP_HIDClass,
			.Class                  = USB_CSCP_VendorSpecificClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = STRING_ID_Product
		},

/*	.HID_GenericHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(GenericReport)
		}, */

	.HID_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = GENERIC_IN_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = GENERIC_EPSIZE,
			.PollingIntervalMS      = 0x05
		},
};

const USB_HID_Descriptor_HID_t PROGMEM Pokey_HID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(HID_Descriptor_Pokey)
};

const USB_HID_Descriptor_HID_t PROGMEM Peggy_HID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

		.HIDSpec                = VERSION_BCD(1,1,1),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(HID_Descriptor_Peggy)
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString = USB_STRING_DESCRIPTOR(L"Entropic Engineering");

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"Orthobox");

const USB_Descriptor_String_t PROGMEM SerialNumber = USB_STRING_DESCRIPTOR(L"0xDEADBEEF");

#define LSTR(str) L ## str
#define N_VAR(var) const USB_Descriptor_String_t PROGMEM NAMED_##var = USB_STRING_DESCRIPTOR(LSTR(#var))

N_VAR(timestamp);
N_VAR(status);
N_VAR(config);
N_VAR(timeout);
N_VAR(error_threshold);
N_VAR(item_order);
N_VAR(wall_error);
N_VAR(duration);
N_VAR(drop_error);
N_VAR(poke);
N_VAR(location);
N_VAR(peg);
N_VAR(new_state);
N_VAR(tool);
N_VAR(event);
N_VAR(event_number);
N_VAR(box_type);
N_VAR(toggle_raw);
N_VAR(raw_values);
N_VAR(hardware_fault);
N_VAR(peg_thresholds);
N_VAR(bootloader);

// TODO: Populate remaining string descriptors.
#define N_CASE(var) case STRING_ID_##var: Address = &NAMED_##var; Size = pgm_read_byte(&NAMED_##var.Header.Size); break;

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;
	UNUSED(wIndex);
	switch (DescriptorType)
	{
		case DTYPE_Device:
			if (box_type == BOX_TYPE_POKEY) {
				Address = &DeviceDescriptorPokey;
			} else {
				Address = &DeviceDescriptor;
			}
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_BOS:
			Address = &BOSDescriptor;
			Size = pgm_read_byte(&BOSDescriptor.TotalLength);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case STRING_ID_Language:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case STRING_ID_Manufacturer:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case STRING_ID_Product:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
				case STRING_ID_Serial_Number:
					Address = &SerialNumber;
					Size    = pgm_read_byte(&SerialNumber.Header.Size);
					break;
				N_CASE(timestamp);
				N_CASE(status);
				N_CASE(config);
				N_CASE(timeout);
				N_CASE(error_threshold);
				N_CASE(item_order);
				N_CASE(wall_error);
				N_CASE(duration);
				N_CASE(drop_error);
				N_CASE(poke);
				N_CASE(location);
				N_CASE(peg);
				N_CASE(new_state);
				N_CASE(tool);
				N_CASE(event);
				N_CASE(event_number);
				N_CASE(box_type);
				N_CASE(toggle_raw);
				N_CASE(raw_values);
				N_CASE(hardware_fault);
				N_CASE(peg_thresholds);
				N_CASE(bootloader);
			}

			break;
		case HID_DTYPE_HID:
			if (box_type == BOX_TYPE_POKEY) {
				Address = &Pokey_HID;
			} else {
				Address = &Peggy_HID;
			}
			Size    = sizeof(USB_HID_Descriptor_HID_t);
			break;
		case HID_DTYPE_Report:
			if (box_type == BOX_TYPE_POKEY) {
				Address = &HID_Descriptor_Pokey;
				Size = sizeof(HID_Descriptor_Pokey);
			} else {
				Address = &HID_Descriptor_Peggy;
				Size = sizeof(HID_Descriptor_Peggy);
			}
			break;
		default:
			Serial_SendString("Uncaught Descriptor Request: "); Serial_SendByte(DescriptorType); Serial_SendByte(0x0A);
	}

	*DescriptorAddress = Address;
	return Size;
}

