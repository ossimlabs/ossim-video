#include <ossimPredator/ossimPredatorKlvTable.h>
#include <iostream>
#include <iomanip> 
#include <ossim/base/ossimTrace.h>
static const ossimTrace traceDebug("ossimPredatorKlvTable:debug");
static const  ossimPredatorKlvInfoType OSSIM_PREDATOR_UDS_TABLE[]=
{
{KLV_KEY_STREAM_ID,"Stream ID",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_ORGANIZATIONAL_PROGRAM_NUMBER,"Organizational Program Number",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_UNIX_TIMESTAMP,"UNIX Timestamp",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x04, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}}, // TIME STAMP
{KLV_KEY_UNIX_TIMESTAMP_RAW,"UNIX Timestamp Raw",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x04, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}}, // TIME STAMP
{KLV_KEY_USER_DEFINED_UTC_TIMESTAMP, "User Defined UTC", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970, "User Defined Timestamp Microseconds since 1970", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}},
{KLV_KEY_VIDEO_START_DATE_TIME_UTC, "Video Timestamp Start Date and Time",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x02, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_TIMESYSTEM_OFFSET, "Time System Offset From UTC", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00}},
{KLV_UAS_DATALINK_LOCAL_DATASET, "UAS Datalink Local Data Set",{0x06, 0x0E, 0x2B, 0x34, 0x02, 0x0B, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00}},
{KLV_BASIC_UNIVERSAL_METADATA_SET, "Universal Metadata Set",{0x06, 0x0E, 0x2B, 0x34, 0x02, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_SECURITY_METADATA_UNIVERSAL_SET, "Security metadata universal set", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x01, 0x01, 0x01, 0x02, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}},
{KLV_URL_STRING, "URL String", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SECURITY_CLASSIFICATION_SET, "Security Classification Set", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x01, 0x01, 0x01, 0x02, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_BYTE_ORDER, "Byte Order", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00}},
{KLV_KEY_MISSION_NUMBER,"Mission Number",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}},
// Security tags
{KLV_KEY_OBJECT_COUNTRY_CODES, "Object Country Codes", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x20, 0x01, 0x02, 0x01, 0x01, 0x00}},
{KLV_KEY_SECURITY_CLASSIFICATION, "Security Classification", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_CLASSIFYING_COUNTRY_AND_RELEASE_INSTRUCTIONS_COUNTRY_CODING_METHOD, "Classifying Country and Releasing Instruction Country Coding Method", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x20, 0x01, 0x02, 0x07, 0x00, 0x00}},
{KLV_KEY_CLASSIFYING_COUNTRY, "Classifying Country", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x20, 0x01, 0x02, 0x08, 0x00, 0x00}},
{KLV_KEY_SECURITY_INFORMATION, "Security-SCI/SHI Information", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x02, 0x02, 0x00, 0x00}},
{KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS, "Release Instructions", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x20, 0x01, 0x02, 0x09, 0x00, 0x00}},
{KLV_KEY_SECURITY_CAVEATS, "Caveats", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_CLASSIFIED_BY, "Classified By", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_DERIVED_FROM, "Derived From", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_CLASSIFICATION_REASON, "Classification Reason", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_DECLASSIFICATION_DATE, "Declassification Date", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_CLASSIFICATION_AND_MARKING_SYSTEM, "Classification and Marking System", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_OBJECT_COUNTRY_CODING_METHOD, "Object Country Coding Method", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x20, 0x01, 0x02, 0x06, 0x00, 0x00}},
{KLV_KEY_CLASSIFICATION_COMMENT, "Classification Comment", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x02, 0x08, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00}},
// Spec says allowing values for 11th byte are 0x05, 0x06, 0x08, 0x09, 0x0B, 0x0C, 0x0D, 0x0F and 12th byte are 0x10, 0x11, 0x12, 0x20, 0x21, 0x22, using only the first of these as test data uses LDS shortened key and not sure which to use
{KLV_KEY_UMID1, "UMID1", {0x06, 0x0A, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x05, 0x10, 0x00, 0x00}},
{KLV_KEY_UMID2, "UMID2", {0x06, 0x0A, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x06, 0x10, 0x00, 0x00}},
{KLV_KEY_UMID3, "UMID3", {0x06, 0x0A, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x08, 0x10, 0x00, 0x00}},
{KLV_KEY_UMID4, "UMID4", {0x06, 0x0A, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x09, 0x10, 0x00, 0x00}},
{KLV_KEY_TRANSPORT_STREAM_ID, "Transport Stream ID", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_ITEM_DESIGNATOR_ID, "Item Designator ID", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x03, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SECURITY_VERSION, "Version", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x05, 0x04, 0x00, 0x00, 0x00}},
{KLV_KEY_CLASSIFYING_COUNTRY_AND_RELEASING_INSTRUCTIONS_COUNTRY_CODE_METHOD_VERSION_DATE, "Classifying Country and Releasing Instructions Country Coding Method Version Date", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x04, 0x03, 0x03, 0x00, 0x00, 0x00}},
{KLV_KEY_OBJECT_COUNTRY_CODING_METHOD_VERSION_DATE, "Object Country Coding Method Version Date", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x04, 0x03, 0x04, 0x00, 0x00, 0x00}},
// End Security Tags
{KLV_KEY_ORIGINAL_PRODUCER_NAME, "Original Producer Name", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_GROUND_SPEED,"Platform Ground Speed",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_MAGNETIC_HEADING_ANGLE,"Platform Magnetic Heading Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x01, 0x08, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_HEADING_ANGLE,"Platform Heading Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x06, 0x00, 0x00, 0x00}},
// In adding LDS support for the next to fields, LDS requires double precision, so duplicating these keys for LDS
{KLV_KEY_PLATFORM_PITCH_ANGLE,"Platform Pitch Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x05, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_ROLL_ANGLE, "Platform Roll Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x04, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_PITCH_ANGLE_FULL,"Platform Pitch Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x05, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_ROLL_ANGLE_FULL, "Platform Roll Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x07, 0x01, 0x10, 0x01, 0x04, 0x00, 0x00, 0x00}},
{KLV_KEY_INDICATED_AIR_SPEED,"Platform Indicated Air Speed",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x01, 0x0B, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_DESIGNATION,"Platform Designation",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_PLATFORM_DESIGNATION2,"Platform Designation",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x21, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_IMAGE_SOURCE_SENSOR,"Image Source Sensor",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x04, 0x20, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_IMAGE_COORDINATE_SYSTEM,"Image Coordinate System",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00}},
{KLV_KEY_SENSOR_LATITUDE,"Sensor Latitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x02, 0x04, 0x02, 0x00}},
{KLV_KEY_SENSOR_LONGITUDE,"Sensor Longitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x02, 0x06, 0x02, 0x00}},
{KLV_KEY_SENSOR_TRUE_ALTITUDE,"Sensor True Altitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x02, 0x01, 0x02, 0x02, 0x00, 0x00}},
{KLV_KEY_SENSOR_HORIZONTAL_FOV,"Sensor Horizontal Field Of View",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x02, 0x04, 0x20, 0x02, 0x01, 0x01, 0x08, 0x00, 0x00}},
{KLV_KEY_SENSOR_VERTICAL_FOV1,"Sensor Vertical Field Of View",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x04, 0x20, 0x02, 0x01, 0x01, 0x0A, 0x01, 0x00}},
{KLV_KEY_SENSOR_VERTICAL_FOV2,"Sensor Vertical Field Of View",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x04, 0x20, 0x02, 0x01, 0x01, 0x0A, 0x01, 0x00}},
{KLV_KEY_SLANT_RANGE,"Slant Range",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x08, 0x01, 0x01, 0x00, 0x00, 0x00}},
{KLV_KEY_OBLIQUITY_ANGLE,"Obliquity Angle",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x10, 0x01, 0x03, 0x00, 0x00, 0x00}},
{KLV_KEY_ANGLE_TO_NORTH, "Angle To North", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x10, 0x01, 0x02, 0x00, 0x00, 0x00}},
{KLV_KEY_TARGET_WIDTH,"Target Width",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x09, 0x02, 0x01, 0x00, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_LATITUDE,"Frame Center Latitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x02, 0x01, 0x03, 0x02, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_LONGITUDE,"Frame Center Longitude",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x02, 0x01, 0x03, 0x04, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_ELEVATION,"Frame Center elevation",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x06, 0x07, 0x01, 0x02, 0x03, 0x10, 0x00, 0x00, 0x00}},   
{KLV_KEY_CORNER_LATITUDE_POINT_1,"Corner Latitude Point 1",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x07, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_1,"Corner Longitude Point 1",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0B, 0x01, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_2,"Corner Latitude Point 2",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x08, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_2,"Corner Longitude Point 2",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0C, 0x01, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_3,"Corner Latitude Point 3",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x09, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_3,"Corner Longitude Point 3",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0D, 0x01, 0x00}},
{KLV_KEY_CORNER_LATITUDE_POINT_4,"Corner Latitude Point 4",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0A, 0x01, 0x00}},
{KLV_KEY_CORNER_LONGITUDE_POINT_4,"Corner Longitude Point 4",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x01, 0x02, 0x01, 0x03, 0x0E, 0x01, 0x00}},
{KLV_KEY_DEVICE_ABSOLUTE_SPEED,"Device Absolute Speed",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_DEVICE_ABSOLUTE_HEADING,"Device Absolute Heading",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x03, 0x01, 0x01, 0x02, 0x00, 0x00}},
{KLV_KEY_ABSOLUTE_EVENT_START_DATE,"Absolute Event Start Date",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x02, 0x01, 0x02, 0x07, 0x01, 0x00, 0x00}},
{KLV_KEY_SENSOR_ROLL_ANGLE,"Sensor Roll Angle", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x10, 0x01, 0x01, 0x00, 0x00, 0x00}},
{KLV_KEY_SENSOR_RELATIVE_ELEVATION_ANGLE,"Sensor Relative Elevation Angle", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x05, 0x00, 0x00, 0x00}},
{KLV_KEY_SENSOR_RELATIVE_AZIMUTH_ANGLE,"Sensor Relative Azimuth Angle", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00}},
{KLV_KEY_SENSOR_RELATIVE_ROLL_ANGLE,"Sensor Relative Roll Angle", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x06, 0x00, 0x00, 0x00}},
{KLV_KEY_UAS_LDS_VERSION_NUMBER,"UAS LDS Version Number", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00}},
{KLV_KEY_GENERIC_FLAG_DATA_01,"Generic Flag Data 01", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00}},
{KLV_KEY_STATIC_PRESSURE,"Static Pressure", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x01, 0x0F, 0x00, 0x00, 0x00}},
{KLV_KEY_SENSOR_ELLIPSOID_HEIGHT,"Sensor Ellipsoid Height",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x01, 0x82, 0x47, 0x00, 0x00}},
{KLV_KEY_FRAME_CENTER_HEIGHT_ABOVE_ELLIPSOID,"Frame Center Height Above Ellipsoid",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x48, 0x00, 0x00, 0x00}},
// KLV_KEY_OPERATIONAL_MODE is LDS Key 77 from MISB STD 0601
{KLV_KEY_OPERATIONAL_MODE,"Operational Mode",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x21, 0x00, 0x00, 0x00}},
// KLV_KEY_SENSOR_NORTH_VELOCITY is LDS Key 79 from MISB STD 0601
{KLV_KEY_SENSOR_NORTH_VELOCITY,"Sensor North Velocity",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x02, 0x7e, 0x00, 0x00, 0x00}},
// KLV_KEY_SENSOR_EAST_VELOCITY is LDS Key 80 from MISB STD 0601
{KLV_KEY_SENSOR_EAST_VELOCITY,"Sensor East Velocity",{0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x02, 0x7f, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_LOCAL_DATA_SET, "VMTI Local Data Set",{0x06, 0x0E, 0x2B, 0x34, 0x02, 0x0B, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x01, 0x02, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_PRECISION_TIME_STAMP, "VMTI Precision Timestamp", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}},
{KLV_KEY_VMTI_PRECISION_TIME_STAMP_RAW, "VMTI Precision Timestamp", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x03, 0x07, 0x02, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00}},
{KLV_KEY_VMTI_SYSTEM_NAME, "VMTI System Name/Description", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x02, 0x7C, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_LS_VERSION_NUMBER, "VMTI LS Version Number", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x05, 0x04, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_TOTAL_TARGETS_DETECTED, "VMTI Total Number of Targets Detected in the Frame", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x36, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_NUMBER_REPORTED_TARGETS, "VMTI Number of Reported Targets", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x37, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_MOTION_IMAGERY_FRAME_NUMBER, "Motion Imagery Frame Number", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x1F, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_FRAME_WIDTH, "VMTI Frame Width", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x07, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_FRAME_HEIGHT, "VMTI Frame Height", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x02, 0x08, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_SOURCE_SENSOR, "VMTI Source Sensor", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x04, 0x20, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00}},
{KLV_KEY_VMTI_SENSOR_HORIZONTAL_FOV, "VMTI Sensor Horizontal Field of View", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x02, 0x04, 0x20, 0x02, 0x01, 0x01, 0x08, 0x00, 0x00}},
{KLV_KEY_VMTI_SENSOR_VERTICAL_FOV, "VMTI Sensor Vertical Field of View", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x07, 0x04, 0x20, 0x02, 0x01, 0x01, 0x0A, 0x01, 0x00}},
{KLV_KEY_VMTI_MOTION_IMAGERY_ID, "VMTI Motion Imagery ID", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x04, 0x05, 0x03, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGETSERIES, "VMTI VTargetSeries", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x04, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x03, 0x1B, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_NUMBER, "Target Centroid Pixel Number", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x38, 0x00, 0x00, 0x00}}, 
{KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_PIXEL_NUMBER, "Bounding Box Top Left Pixel Number", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x39, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_PIXEL_NUMBER, "Bounding Box Bottom Right Pixel Number", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x3A, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_PRIORITY, "Target Priority", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x3B, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_CONFIDENCE_LEVEL, "Target Confidence Level", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x3C, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_NEW_DETECTION_FLAG_TARGET_HISTORY, "New Detection Flag/Target History", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x3D, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_PERCENTAGE_OF_TARGET_PIXELS, "Percentage of Target Pixels", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x3E, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_COLOR, "Target Color", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x3F, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_INTENSITY, "Target Intensity", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x40, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_LOCATION_LATITUDE_OFFSET, "Target Location Latitude Offset", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x41, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_LOCATION_LONGITUDE_OFFSET, "Target Location Longitude Offset", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x42, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_HEIGHT, "Target Height", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x43, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_LATITUDE_OFFSET, "Bounding Box Top Left Latitude Offset", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x44, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_LONGITUDE_OFFSET, "Bounding Box Top Left Longitude Offset", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x45, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_LATITUDE_OFFSET, "Bounding Box Bottom Right Latitude Offset", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x46, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_LONGITUDE_OFFSET, "Bounding Box Bottom Right Longitude Offset", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x47, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_LOCATION, "Target Location", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x05, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x03, 0x14, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_BOUNDARY, "Target Boundary", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x04, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x03, 0x17, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_ROW, "Target Centroid Pixel Row", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x58, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_COLUMN, "Target Centroid Pixel Column", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x02, 0x03, 0x59, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_FPA_INDEX, "FPA Index", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x05, 0x01, 0x01, 0x0E, 0x01, 0x03, 0x03, 0x59, 0x1D, 0x01, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_LATITUDE, "VMTI Boundary Location Latitude", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x28, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_LONGITUDE, "VMTI Boundary Location Longitude", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x29, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_HEIGHT, "VMTI Boundary Location Height", {0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x2A, 0x00, 0x00, 0x00}},
{KLV_KEY_VMTI_VTARGET_PACK_ID, "VMTI VTarget Pack ID", {0x06, 0x0E, 0x2B, 0x34, 0x02, 0x05, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x03, 0x07, 0x00, 0x00, 0x00}},
{KLV_KEY_INVALID,"Invalid Key",{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

const ossim_uint8 ossimPredatorKlvTable::theKlvKey[4] = { 0x06,0x0e,0x2b,0x34 };
#define PRINT_KEY(x) printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n", \
(x)[0], (x)[1], (x)[2], (x)[3], (x)[4], (x)[5], (x)[6], (x)[7], (x)[8], (x)[9], (x)[10], (x)[11], (x)[12], (x)[13], (x)[14], (x)[15])

static double mapValue(double value, double a, double b, double targetA, double targetB)
{
   double t = (value - a)/(b-a);
   return (targetA + (t*(targetB-targetA)));
}

ossimPredatorKlvTable::Node ossimPredatorKlvTable::convertValue(int id, const std::vector<ossim_uint8>& bufferValue)
{
  ossimPredatorKlvTable::Node result;
  result.theId = id;
  switch(id)
  {
    case KLV_KEY_FRAME_CENTER_LATITUDE:
    case KLV_KEY_SENSOR_LATITUDE:
    {
      ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&bufferValue.front());
      if(theNeedToSwapFlag)
      {
         theEndian.swap(buf);
      }

      //LAT: Map -(2^31-1)..(2^31-1) to +/-90.
      ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90, 90);//(360.0*(((double)buf + 2147483647.0)/(4294967294.0)))-180.0; //180.0*((buf)/(double)((ossim_int64)(1<<31) - 1));
      //std::cout << "LAT == " << value << std::endl;
      if(theNeedToSwapFlag)
      {
         theEndian.swap(value);
      }
      ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
      result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
      //            std::cout << "SENSOR LAT!!" << std::endl;
      break;
    }

    case KLV_KEY_FRAME_CENTER_LONGITUDE:
    case KLV_KEY_SENSOR_LONGITUDE:
    {
      ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&bufferValue.front());
      if(theNeedToSwapFlag)
      {
         theEndian.swap(buf);
      }

      //LAT: Map -(2^31-1)..(2^31-1) to +/-180.
      ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180, 180);//(360.0*(((double)buf + 2147483647.0)/(4294967294.0)))-180.0; //180.0*((buf)/(double)((ossim_int64)(1<<31) - 1));
      //std::cout << "LAT == " << value << std::endl;
      if(theNeedToSwapFlag)
      {
         theEndian.swap(value);
      }
      ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
      result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
      //            std::cout << "SENSOR LAT!!" << std::endl;
      break;
    }
    case KLV_KEY_SENSOR_TRUE_ALTITUDE:
    {
      ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&bufferValue.front());
      if(theNeedToSwapFlag)
      {
         theEndian.swap(buf);
      }
      ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000); 
      //std::cout << "ALTITUDE == " << value << std::endl;
      if(theNeedToSwapFlag)
      {
         theEndian.swap(value);
      }
      ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
      result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);

      break;
    }
    case KLV_KEY_SENSOR_RELATIVE_ELEVATION_ANGLE:
    {
      //Map -(2^31-1)..(2^31-1) to +/-180.
      ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&bufferValue.front());
      if(theNeedToSwapFlag)
      {
         theEndian.swap(buf);
      }
      ossim_float64 value  = mapValue(buf, -2147483647.0,2147483647.0,-180.0,180.0);
      //std::cout << "REALATIVE Elevation == " << value << std::endl;
      if(theNeedToSwapFlag)
      {
         theEndian.swap(value);
      }
      ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
      result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
      break;
    }
    case KLV_KEY_SENSOR_VERTICAL_FOV1:
    case KLV_KEY_SENSOR_VERTICAL_FOV2:
    case KLV_KEY_SENSOR_HORIZONTAL_FOV:
    {
      // Map 0..(2^16-1) to 0..180.
      ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&bufferValue.front());
      if(theNeedToSwapFlag)
      {
         theEndian.swap(buf);
      }
      ossim_float32 value  = mapValue(buf, 0, 65535, 0, 180); 
      //std::cout << "VFOV == " << value << std::endl;
      if(theNeedToSwapFlag)
      {
         theEndian.swap(value);
      }
      ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
      result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+4);
      break;  
    }
     case KLV_KEY_SENSOR_RELATIVE_AZIMUTH_ANGLE://KLV_KEY_SENSOR_RELATIVE_AZIMUTH_ANGLE
     {
        // Map 0..(2^32-1) to 0..360.
      ossim_uint32 buf = *reinterpret_cast<const ossim_uint32*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float64 value  = mapValue(buf, 0, 4294967295, 0, 360); 
        //std::cout << "REALATIVE AZIMUTH == " << value << std::endl;
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
       //            std::cout << "SENSOR REALTIVE AZIMUTH ANGLE!!" << std::endl;
        break;
     }
     case KLV_KEY_SENSOR_RELATIVE_ROLL_ANGLE: //KLV_KEY_SENSOR_RELATIVE_ROLL_ANGLE
     {
        //0..(2^32-1) to 0..360.
        ossim_uint32 buf = *reinterpret_cast<const ossim_uint32*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float64 value  = mapValue(buf, 0, 4294967295, 0, 360); 
        //std::cout << "REALATIVE roll == " << value << std::endl;
        //            std::cout << "SENSOR REALTIVE ROLL ANGLE!!" << std::endl;
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
        break;
     }
     case KLV_KEY_SLANT_RANGE: // KLV_KEY_SLANT_RANGE
     {
        // Map 0..(2^32-1) to 0..5000000
        ossim_uint32 buf = *reinterpret_cast<const ossim_uint32*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float64 value  = mapValue(buf, 0, 4294967295, 0, 5000000); 
        //std::cout << "SLANT range == " << value << std::endl;
        //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
        break;
     }
     case KLV_KEY_TARGET_WIDTH: //KLV_KEY_TARGET_WIDTH
     {
        //Map 0..(2^16-1) to 0..10000
        ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float32 value  = mapValue(buf, 0, 65535, 0, 10000); 
        //std::cout << "TARGET width == " << value << std::endl;
        //            std::cout << "TARGET WIDTH!!" << std::endl;
         if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+4);
        break;
     }
     case KLV_KEY_FRAME_CENTER_ELEVATION:
     {
       // Map 0..(2^16-1) to -900..19000
        ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000); 
        //std::cout << "FRAME CENTER ELEV == " << value << std::endl;
        //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
        break;
     }
     case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_1:
     case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_1:
     case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_2:
     case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_2:
     case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_3:
     case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_3:
     case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_4:
     case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_4:
     {
        // Map -(2^15-1)..(2^15-1) to +/-0.075.
        ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
        break;
     }
     case KLV_KEY_STATIC_PRESSURE:
     {
        // Map 0..(2^16-1) to 0..5000 mbar.
        ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_uint16 value  = mapValue(buf, 0, 65535, 0, 5000); 
        
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+2);
        break;
     }
     case KLV_KEY_PLATFORM_MAGNETIC_HEADING_ANGLE:// KLV_KEY_PLATFORM_MAGNETIC_HEADING_ANGLE
     {
        // Map 0..(2^16-1) to 0..360.
        ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&bufferValue.front());
        if(theNeedToSwapFlag)
        {
           theEndian.swap(buf);
        }
        ossim_float64 value  = mapValue(buf, 0, 65535, 0, 360); 
        if(theNeedToSwapFlag)
        {
           theEndian.swap(value);
        }
        ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
        result.theValue = std::vector<ossim_uint8>(tempBuf, tempBuf+8);
       //            std::cout << "SENSOR REALTIVE AZIMUTH ANGLE!!" << std::endl;
       // platform magnetic heading
        break;
     }
    default:
    {
      result.theValue = bufferValue;
    }
  
  }
  return result;
}

static void printHex(const std::vector<ossim_uint8>& buf)
{
   ossim_uint32 idx = 0;
   while(idx < buf.size())
   {
      printf("%02X ", buf[idx]);
      if((idx%32) == 0)
      {
        // printf("\n");      
      }
      ++idx;
   }
}

bool ossimPredatorKlvTable::addKeys(const std::vector<ossim_uint8>& buffer)
{
   return addKeys(&buffer.front(), buffer.size());
}

ossim_int64 klv_decode_length(const ossim_uint8* buf, ossim_uint32& offset)
{
   ossim_int64 size = buf[offset];
   ossim_uint8 longTest = buf[offset];
   ++offset;
   if (longTest & 0x80)
   { /* long form */
      int bytes_num = longTest & 0x7f;
      /* SMPTE 379M 5.3.4 guarantee that bytes_num must not exceed 8 bytes */
      if (bytes_num > 8)
      {
         return -1;
      }
      size = 0;
      
      while (bytes_num--)
      {
         size = size << 8 | buf[offset];
         ++offset;
      }
   }
   
   return size;
}

ossim_uint64 decode_length(const ossim_uint8* buf, ossim_uint32& offset)
{
   ossim_uint64 size = buf[offset];
   ossim_uint8 longTest = buf[offset];
   ++offset;
   if (longTest & 0x80)
   { /* long form */
      int bytes_num = longTest & 0x7f;
      /* SMPTE 379M 5.3.4 guarantee that bytes_num must not exceed 8 bytes */
      if (bytes_num > 8)
      {
         return -1;
      }
      size = 0;

      while (bytes_num--)
      {
         size = size << 8 | buf[offset];
         ++offset;
      }
   }
  
   return size;
}


ossim_uint32 lds_decode_key(const ossim_uint8* buf, ossim_uint32& offset)
{
   ossim_uint32 key = buf[offset++];
   //std::cout << "OLD KEY: " << ossimString::toString(key) << std::endl;
   // Have more if highest bit set
   if (key & 0x80)
   { 
      //std::cout << "TRIM KEY1: " << ossimString::toString(key ^ 0x80) << std::endl;
      key = (key ^ 0x80) << 7;
      //std::cout << "SHIFT KEY: " << ossimString::toString(key) << std::endl;
      key = (buf[offset++] & 0x7f) | key;
      //std::cout << "2nd byte " << ossimString::toString(buf[offset]) << std::endl;
      //std::cout << "NEW KEY: " << ossimString::toString(key) << std::endl;
   }
  
   return key;
}

ossimPredatorKlvTable::ossimPredatorKlvTable()
{
   theNeedToSwapFlag = theEndian.getSystemEndianType()!=OSSIM_BIG_ENDIAN;
}

bool ossimPredatorKlvTable::addKeys(const ossim_uint8* buffer, ossim_uint32 length)
{
  // std::cout << "addKeys---------------------------------\n";
  // std::cout << "ADDING KEYS!!!!!!!!!!!!\n";
   std::vector<ossim_uint8> bufferToParse;
   bufferToParse = theNeedToParseBuffer;
   if(buffer)
   {
      bufferToParse.insert(bufferToParse.end(),
                           buffer,
                           buffer + length);

   }
   theNeedToParseBuffer.clear();
   ossim_uint32 currentIdx = 0;
   ossim_uint32 totalLen = bufferToParse.size();
  // std::cout << "BUFFER TOTAL SIZE: " << totalLen << std::endl;
   if(totalLen < 1){
    //std::cout << "FIRST RETURN!!!!!!!!\n";
    return false;
   } 
   const ossim_uint8* bufPtr = &bufferToParse.front();
   //PRINT_KEY(&bufPtr[currentIdx]);
   while(std::equal(theKlvKey,
                    theKlvKey + 4,
                    &bufPtr[currentIdx])) // while we are looking at klv keys keep parsing
   {
      //std::cout << "CURRENT IDX, totallength ==== " << currentIdx << "," << totalLen << std::endl;
      //std::cout << "((currentIdx+16) >= totalLen)?" << ((currentIdx+16) >= totalLen) << std::endl;
      if((currentIdx+16) >= totalLen)
      {
         theNeedToParseBuffer.clear();
         theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                     &bufPtr[currentIdx],
                                     &bufPtr[totalLen]);
  //  std::cout << "SECOND RETURN!!!!!!!!\n";
         return true;
      }
      ossimPredatorKlvTable::Node node;
      ossim_uint32 saveIdx = currentIdx;
      ossim_int32 indexValue = findPredatorKlvIndex(&bufPtr[currentIdx]);

      if(indexValue >= 0)
      {
        node.theId = OSSIM_PREDATOR_UDS_TABLE[indexValue].theId;
      }
      else
      {
        node.theId = KLV_KEY_INVALID;
      }
      if(node.theId < 0)
      {
         if(traceDebug())
         {
            ossim_uint32 tempId = currentIdx + 16;
            std::cout << "**************UNDEFINED KEY**************\n";
            std::cout << "WITH SIZE === " << klv_decode_length(bufPtr, tempId) << std::endl;
            PRINT_KEY(&bufPtr[currentIdx]);
         }
         //if(bufPtr[currentIdx] == 0xff) return false;
         //ossim_uint32 tempId = currentIdx + 16;
         //std::cout << "**************UNDEFINED KEY**************\n";
         //std::cout << "WITH SIZE === " << klv_decode_length(bufPtr, tempId) << std::endl;
         // PRINT_KEY(&bufPtr[currentIdx]);
         //
         //ossim_float32 f = *reinterpret_cast<const ossim_float32*>(&bufPtr[tempId]);
         //theEndian.swap(f);
         //          std::cout << "POSSIBLE VALUE === " << f << std::endl; 
      }
    //  PRINT_KEY(&bufPtr[currentIdx]);
      currentIdx += 16;
      int klvLength = klv_decode_length(bufPtr, currentIdx);
      //std::cout << "offsets: " << (currentIdx+klvLength) << std::endl;
      if(klvLength > 0)
      {
         bool needMore = false;
         if((currentIdx + klvLength) <= totalLen)
         {
            node.theValue.insert(node.theValue.end(),
                                 &bufPtr[currentIdx], &bufPtr[currentIdx + klvLength]);
            currentIdx += klvLength;
            //std::cout << "KLV LENGTH ======= " << klvLength << std::endl;
            if(node.theId >=0)
            {
              //std::cout << "node.theId?  " << node.theId << std::endl;
               if((node.theId == KLV_BASIC_UNIVERSAL_METADATA_SET)||
                  (node.theId == KLV_KEY_SECURITY_CLASSIFICATION_SET)||
                  (node.theId == KLV_SECURITY_METADATA_UNIVERSAL_SET))
               {
                 addAbsoluteKeyDefinitions(node.theValue, needMore);
               }
               /*
               if((node.theId == KLV_BASIC_UNIVERSAL_METADATA_SET)||
                  (node.theId == KLV_KEY_SECURITY_CLASSIFICATION_SET))
               {
                  ossim_uint32 tempIdx = 0;
                  while(tempIdx < node.theValue.size())
                  {
                     if(node.theValue[tempIdx] == 0x06)
                     {
                        break;
                     }
                     ++tempIdx;
                  }
                     //addKeys(&node.theValue[tempIdx], node.theValue.size() - tempIdx);


                  if(currentIdx < totalLen)
                  {
                     theNeedToParseBuffer.insert(theNeedToParseBuffer.begin(),
                                                 &bufPtr[currentIdx],
                                                 &bufPtr[totalLen]);
                  }
//                  std::cout << "??????????????";
                  if(tempIdx < node.theValue.size())
                      theNeedToParseBuffer.insert(theNeedToParseBuffer.begin(),
                                                  node.theValue.begin()+tempIdx,
                                                  node.theValue.end());
                  //node.theValue.clear();
                  //node.theId = -1;
                  //PRINT_KEY(&theNeedToParseBuffer.front());
                  ////std::cout << "CALLING RECURSIVE!!!!!!!!!!!!!!!!!!!!!!" << node.theId << std::endl;
                  return addKeys(0,0);

               }
               */
               else if(node.theId == KLV_UAS_DATALINK_LOCAL_DATASET)
               {
                //std::cout << "KLV_UAS_DATALINK_LOCAL_DATASET\n";
                 klvMapType tempTable;
                 ossim_uint16 checksum;
                 // lod 16 byte key
                 std::vector<ossim_uint8> checksumBuffer(&bufPtr[saveIdx], &bufPtr[currentIdx-2]);
                 addUasDatalinkLocalDataSet(node.theValue, tempTable, checksum);

                 // now verify checksum
                 ossim_uint16 checksumCompare = compute16BitChecksum(checksumBuffer);

                 if(checksum == checksumCompare)
                 {
                    klvMapType::iterator iter = tempTable.begin();
                    while(iter != tempTable.end())
                    {
                      theKlvParameters.insert(std::make_pair(iter->first, iter->second));
                      ++iter;
                    }
                 }
                 else
                 {
                  std::cout << "WHAT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                 }
 
                  //print(std::cout);
                  //node.theValue.clear();
                  //node.theId = -1;
                 // std::cout << "CURRENT IDX ====== " << currentIdx << ", " << totalLen << std::endl;
                 // if(currentIdx < totalLen)
                 // {
                 //    theNeedToParseBuffer.insert(theNeedToParseBuffer.begin(),
                 //                                &bufPtr[currentIdx],
                 //                                &bufPtr[totalLen]);
                 // }
                 // if(currentIdx == totalLen)
                 // {
                 //    return false;
                 // }
               }
               else
               {
                //if(klvLength > 16)
               // {
               //   addAbsoluteKeyDefinitions(node.theValue, needMore);

                //}
                //else
               // {
//                  std::cout << "INSERTING THIS THING HERE!!!!\n";
//                  std::cout << "KLV LENGTH ========================= " << klvLength << std::endl;
                  theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(node.theId),
                                                        convertValue(node.theId, node.theValue)));
                //}
               }
                 if(needMore)
                 {

//                    std::cout << "DOING MORE STUFFFFF!!!!!!!!!!!!" << std::endl;
                    ossim_uint32 tempIdx = currentIdx - (klvLength+16);
                    theNeedToParseBuffer.clear();
                    theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                     &bufPtr[tempIdx],
                                     &bufPtr[totalLen]);

//    std::cout << "THIRD RETURN!!!!!!!!\n";
                    return true;
                 }


            }
         }
         else
         {
            theNeedToParseBuffer.clear();

            theNeedToParseBuffer.insert(theNeedToParseBuffer.end(),
                                        &bufPtr[saveIdx],
                                        &bufPtr[totalLen]);
//    std::cout << "FOURTH RETURN!!!!!!!!\n";
            return true;
         }
      }
   }

//std::cout << this->print(std::cout);
//std::cout << "___________________________\n";
//    std::cout << "FIFTH RETURN!!!!!!!!\n";
   return false;
}


void ossimPredatorKlvTable::clear()
{
   theKlvParameters.clear();
}

void ossimPredatorKlvTable::addAbsoluteKeyDefinitions(const std::vector<ossim_uint8>& buffer,
                                                      bool& needMore)
{
   needMore = false;
   ossim_uint32 currentIdx = 0;
   ossim_uint32 bufferSize = buffer.size();
   while(currentIdx < bufferSize)
   {
      if(buffer[currentIdx] == 0x06)
      {
        break;
      }
      ++currentIdx;
   }
   const ossim_uint8* bufPtr = &buffer.front();

   while((currentIdx < bufferSize)&&
         (std::equal(theKlvKey,
                    theKlvKey + 4,
                    &bufPtr[currentIdx])))
   {
      if((currentIdx+16) >= bufferSize)
      {
        break;
      }
      ossimPredatorKlvTable::Node node;
      ossim_uint32 saveIdx = currentIdx;
      ossim_int32 klvIndex = findPredatorKlvIndex(&bufPtr[currentIdx]);
      if(klvIndex >= 0)
      {
        node.theId = OSSIM_PREDATOR_UDS_TABLE[klvIndex].theId;
      }
      else
      {
        node.theId = KLV_KEY_INVALID;
      }
//      if(node.theId < 0)
//      {
//      }
      currentIdx += 16;
      int klvLength = klv_decode_length(bufPtr, currentIdx);
      //std::cout << "offsets: " << (currentIdx+klvLength) << std::endl;
      if(klvLength > 0)
      {

         if((currentIdx + klvLength) <= bufferSize)
         {
            std::vector<ossim_uint8> value;

            value.insert(value.end(),
                         &bufPtr[currentIdx], &bufPtr[currentIdx + klvLength]);
            if(node.theId >=0)
            {
              node = convertValue(node.theId, value);
             // switch(node.theId)
             // {
             //   default:
             //   {
                  theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(node.theId),
                                                         node));
             //     break;
             //   }
             // }
            }
         }
         currentIdx += klvLength;
      }
   }
   if(currentIdx < bufferSize) needMore = true;
}

bool ossimPredatorKlvTable::valueAsString(ossimString& result,
                                          ossimPredatorKlvIndex id, int set, int index)const
{
   bool foundFlag = false;
   
   klvMapType::const_iterator i; //= theKlvParameters.find(id);
   
   // Need to support printing duplicate values for the same key
   if (set > 0 || index > 0) 
   {
     for (klvMapType::const_iterator range=theKlvParameters.equal_range(id).first; range!=theKlvParameters.equal_range(id).second; ++range)
     {
        if (range->second.theIndex == index && range->second.theSet == set) i = range;
     }
   }
   else
   {
     i = theKlvParameters.find(id);
   }
      
   if(i != theKlvParameters.end())
   {
      foundFlag = true;
      switch(i->second.theId)
      {
            // convert ossim_uint64 types
         case KLV_KEY_UNIX_TIMESTAMP:
         case KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970:
	 case KLV_KEY_VMTI_PRECISION_TIME_STAMP:
         {
//          std::cout << "ossimPredatorKlvTable::valueAsString: byte size ===== " <<i->second.theValue.size() << std::endl; 
            ossim_uint64 value = *reinterpret_cast<const ossim_uint64*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
	    ossimDate klvdate;
            if(getDate(klvdate, true))
	    {
 	      std::ostringstream datestr;
	      ossim_uint32 roundStart = klvdate.getFractionalSecond() * 1000;

              datestr << std::setw(4) << std::setfill('0') << klvdate.getYear() << "-"
   		<< std::setw(2) << std::setfill('0') << klvdate.getMonth() << "-"
   		<< std::setw(2) << std::setfill('0') << klvdate.getDay() << " "
   		<< std::setw(2) << std::setfill('0') << klvdate.getHour() << ":"
   		<< std::setw(2) << std::setfill('0') << klvdate.getMin() << ":"
   		<< std::setw(2) << std::setfill('0') << klvdate.getSec() << "."
		<< std::setw(3) << std::setfill('0') << roundStart;
  
	      result = ossimString(datestr.str());
	    }
            break;
         }
	 case KLV_KEY_UNIX_TIMESTAMP_RAW:
	 case KLV_KEY_VMTI_PRECISION_TIME_STAMP_RAW:
	 {
            ossim_uint64 value = *reinterpret_cast<const ossim_uint64*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
	    result = ossimString::toString(value);

            break;
	 }
         // convert uint64 values
         case KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_NUMBER:
         case KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_PIXEL_NUMBER:
         case KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_PIXEL_NUMBER:
	 //case KLV_KEY_VMTI_PRECISION_TIME_STAMP_RAW:
         {
            ossim_uint64 value = *reinterpret_cast<const ossim_uint64*>(&(i->second.theValue.front()));
            result = ossimString::toString(value);

            break;
         }
	 // convert uint32
         case KLV_KEY_VMTI_TOTAL_TARGETS_DETECTED:
	 case KLV_KEY_VMTI_NUMBER_REPORTED_TARGETS:
	 case KLV_KEY_VMTI_MOTION_IMAGERY_FRAME_NUMBER:
	 case KLV_KEY_VMTI_FRAME_WIDTH:
	 case KLV_KEY_VMTI_FRAME_HEIGHT:
         case KLV_KEY_VMTI_VTARGET_TARGET_COLOR:
         case KLV_KEY_VMTI_VTARGET_TARGET_INTENSITY:
	 case KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_ROW:
         case KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_COLUMN:
	 case KLV_KEY_VMTI_VTARGET_PACK_ID:
         {
            ossim_uint32 value = *reinterpret_cast<const ossim_uint32*>(&(i->second.theValue.front()));
            result = ossimString::toString(value);

            break;
         }
         case KLV_KEY_VMTI_VTARGET_NEW_DETECTION_FLAG_TARGET_HISTORY:
         {
            ossim_uint16 value = *reinterpret_cast<const ossim_uint16*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
            result = ossimString::toString(value);

            break;
         }
         // convert uint16 values
         case KLV_KEY_GENERIC_FLAG_DATA_01:
         case KLV_KEY_INDICATED_AIR_SPEED:
         case KLV_KEY_PLATFORM_GROUND_SPEED:
         case KLV_KEY_UAS_LDS_VERSION_NUMBER:
	 case KLV_KEY_VMTI_LS_VERSION_NUMBER:
         {
            ossim_uint16 value = *reinterpret_cast<const ossim_uint16*>(&(i->second.theValue.front()));
            result = ossimString::toString(value);

            break;
         }
	 // uint8 values 
         case KLV_KEY_STREAM_ID:
         case KLV_KEY_VMTI_VTARGET_TARGET_PRIORITY:
         case KLV_KEY_VMTI_VTARGET_TARGET_CONFIDENCE_LEVEL:
	 case KLV_KEY_VMTI_VTARGET_PERCENTAGE_OF_TARGET_PIXELS:
         {
            ossim_uint8 value = *reinterpret_cast<const ossim_uint8*>(&(i->second.theValue.front()));
            result = ossimString::toString(value);

            break;
	 }
	 case KLV_KEY_OPERATIONAL_MODE:
	 {
	    ossim_uint8 value = *reinterpret_cast<const ossim_uint8*>(&(i->second.theValue.front()));
	    switch (value)
	    {
	      case 0:
	        result = "Other";
		break;
              case 1:
                result = "Operational";
                break;
              case 2:
                result = "Training";
                break;
              case 3:
                result = "Exercise";
                break;
              case 4:
                result = "Maintenance";
                break;
              case 5:
                result = "Test";
                break;
	      default:
		result = "Unknown";
		break;
	    }
	    break;
	 }
	 case KLV_KEY_CLASSIFYING_COUNTRY_AND_RELEASE_INSTRUCTIONS_COUNTRY_CODING_METHOD:
         {
            ossim_uint8 value = *reinterpret_cast<const ossim_uint8*>(&(i->second.theValue.front()));
            switch (value)
            {
              case 1:
                result = "ISO-3166 Two Letter";
                break;
              case 2:
                result = "ISO-3166 Three Letter";
                break;
              case 3:
                result = "FIPS 10-4 Two Letter";
                break;
              case 4:
                result = "FIPS 10-4 Four Letter";
                break;
              case 5:
                result = "ISO-3166 Numeric";
                break;
              case 6:
                result = "1059 Two Letter";
                break;
              case 7:
                result = "1059 Three Letter";
                break;
	      case 10:
		result = "FIPS 10-4 Mixed";
		break;
              case 11:
                result = "ISO 3166 Mixed";
                break;
              case 12:
                result = "STANAG 1059 Mixed";
                break;
              case 13:
                result = "GENC Two Letter";
                break;
              case 14:
                result = "GENC Three Letter";
                break;
              case 15:
                result = "GENC Numeric";
                break;
              case 16:
                result = "GENC Mixed";
                break;
              default:
                result = "Omitted Value";
                break;
            }
            break;
         }
         case KLV_KEY_OBJECT_COUNTRY_CODING_METHOD:
         {
            ossim_uint8 value = *reinterpret_cast<const ossim_uint8*>(&(i->second.theValue.front()));
            switch (value)
            {
              case 1:
                result = "ISO-3166 Two Letter";
                break;
              case 2:
                result = "ISO-3166 Three Letter";
                break;
              case 3:
                result = "ISO-3166 Numeric";
                break;
              case 4:
                result = "FIPS 10-4 Two Letter";
                break;
              case 5:
                result = "FIPS 10-4 Four Letter";
                break;
              case 6:
                result = "1059 Two Letter";
                break;
              case 7:
                result = "1059 Three Letter";
                break;
              case 13:
                result = "GENC Two Letter";
                break;
              case 14:
                result = "GENC Three Letter";
                break;
              case 15:
                result = "GENC Numeric";
                break;
              case 64:
                result = "GENC AdminSub";
                break;
              default:
                result = "Omitted Value";
                break;
            }
            break;
         }
         // convert uint16 values
         case KLV_KEY_STATIC_PRESSURE:
	 case KLV_KEY_TRANSPORT_STREAM_ID:
	 case KLV_KEY_SECURITY_VERSION:
         {
            ossim_uint16 value = *reinterpret_cast<const ossim_uint16*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
           result = ossimString::toString(value);
            break;
         }
            // convert string values
         case KLV_KEY_OBJECT_COUNTRY_CODES:
         case KLV_KEY_MISSION_NUMBER:
         case KLV_KEY_ORGANIZATIONAL_PROGRAM_NUMBER:
         case KLV_URL_STRING:
         case KLV_KEY_CLASSIFICATION_COMMENT:
         case KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS:
         case KLV_KEY_SECURITY_CAVEATS:
         case KLV_KEY_SECURITY_CLASSIFICATION:
         case KLV_KEY_ORIGINAL_PRODUCER_NAME:
         case KLV_TIMESYSTEM_OFFSET:
         case KLV_KEY_BYTE_ORDER:
         case KLV_KEY_PLATFORM_DESIGNATION:
         case KLV_KEY_PLATFORM_DESIGNATION2:
         case KLV_KEY_IMAGE_SOURCE_SENSOR:
         case KLV_KEY_IMAGE_COORDINATE_SYSTEM:
         case KLV_KEY_ABSOLUTE_EVENT_START_DATE:
         case KLV_KEY_VIDEO_START_DATE_TIME_UTC:
         case KLV_KEY_PLATFORM_TAIL_NUMBER:
         case KLV_KEY_SECURITY_INFORMATION:
         case KLV_KEY_CLASSIFIED_BY:
         case KLV_KEY_DERIVED_FROM:
         case KLV_KEY_CLASSIFICATION_REASON:
         case KLV_KEY_DECLASSIFICATION_DATE:
         case KLV_KEY_CLASSIFICATION_AND_MARKING_SYSTEM:
	 case KLV_KEY_UMID1:
         case KLV_KEY_UMID2:
         case KLV_KEY_UMID3:
         case KLV_KEY_UMID4:
         case KLV_KEY_ITEM_DESIGNATOR_ID:
         case KLV_KEY_CLASSIFYING_COUNTRY_AND_RELEASING_INSTRUCTIONS_COUNTRY_CODE_METHOD_VERSION_DATE:
         case KLV_KEY_OBJECT_COUNTRY_CODING_METHOD_VERSION_DATE:
	 case KLV_KEY_VMTI_SYSTEM_NAME:
	 case KLV_KEY_VMTI_SOURCE_SENSOR:
         {
				if(i->second.theValue.size()>0)
				{
					const char* bufPtr = reinterpret_cast<const char*>(&(i->second.theValue.front()));
					result = ossimString(bufPtr,
												bufPtr+i->second.theValue.size());
				}
				else
				{
					result = "";
				}
            break;
         }
            // convert double precision values
         case KLV_KEY_SENSOR_RELATIVE_ELEVATION_ANGLE:
         case KLV_KEY_PLATFORM_MAGNETIC_HEADING_ANGLE:
         case KLV_KEY_SENSOR_RELATIVE_ROLL_ANGLE:
         case KLV_KEY_SENSOR_RELATIVE_AZIMUTH_ANGLE:
         case KLV_KEY_SENSOR_LATITUDE:
         case KLV_KEY_SENSOR_LONGITUDE:
         case KLV_KEY_FRAME_CENTER_LATITUDE:
         case KLV_KEY_FRAME_CENTER_LONGITUDE:
         case KLV_KEY_CORNER_LATITUDE_POINT_1:
         case KLV_KEY_CORNER_LATITUDE_POINT_2:
         case KLV_KEY_CORNER_LATITUDE_POINT_3:
         case KLV_KEY_CORNER_LATITUDE_POINT_4:
         case KLV_KEY_CORNER_LONGITUDE_POINT_1:
         case KLV_KEY_CORNER_LONGITUDE_POINT_2:
         case KLV_KEY_CORNER_LONGITUDE_POINT_3:
         case KLV_KEY_CORNER_LONGITUDE_POINT_4:
         case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_1:
         case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_1:
         case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_2:
         case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_2:
         case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_3:
         case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_3:
         case KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_4:
         case KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_4:
	 case KLV_KEY_SENSOR_ELLIPSOID_HEIGHT:
	 case KLV_KEY_FRAME_CENTER_HEIGHT_ABOVE_ELLIPSOID:
         case KLV_KEY_PLATFORM_PITCH_ANGLE_FULL:
         case KLV_KEY_PLATFORM_ROLL_ANGLE_FULL:
	 case KLV_KEY_SENSOR_NORTH_VELOCITY:
	 case KLV_KEY_SENSOR_EAST_VELOCITY:
	 case KLV_KEY_VMTI_VTARGET_TARGET_HEIGHT:
	 case KLV_KEY_VMTI_VTARGET_TARGET_LOCATION_LATITUDE_OFFSET:
	 case KLV_KEY_VMTI_VTARGET_TARGET_LOCATION_LONGITUDE_OFFSET:
         case KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_LATITUDE_OFFSET:
         case KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_LONGITUDE_OFFSET:
         case KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_LATITUDE_OFFSET:
         case KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_LONGITUDE_OFFSET:
	 case KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_HEIGHT:
         case KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_LATITUDE:
         case KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_LONGITUDE:
         {
            ossim_float64 value = *reinterpret_cast<const ossim_float64*>(&(i->second.theValue.front()));
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
            result = ossimString::toString(value);
            break;
         }
         case KLV_KEY_SENSOR_TRUE_ALTITUDE:
         case KLV_KEY_FRAME_CENTER_ELEVATION:
         case KLV_KEY_SLANT_RANGE:
         case KLV_KEY_TARGET_WIDTH:
         case KLV_KEY_SENSOR_ROLL_ANGLE:
         case KLV_KEY_SENSOR_HORIZONTAL_FOV:
         case KLV_KEY_SENSOR_VERTICAL_FOV1:
         case KLV_KEY_SENSOR_VERTICAL_FOV2:
         case KLV_KEY_PLATFORM_HEADING_ANGLE:
         case KLV_KEY_PLATFORM_PITCH_ANGLE:
         case KLV_KEY_PLATFORM_ROLL_ANGLE:
         case KLV_KEY_OBLIQUITY_ANGLE:
         case KLV_KEY_ANGLE_TO_NORTH:
         case KLV_KEY_DEVICE_ABSOLUTE_SPEED:
         case KLV_KEY_DEVICE_ABSOLUTE_HEADING:

         {
            ossim_float32 value = *reinterpret_cast<const ossim_float32*>(&(i->second.theValue.front()));
            
            if(theNeedToSwapFlag)
            {
               theEndian.swap(value);
            }
            result = ossimString::toString(value);
            break;
         }
      }
   }
   result = result.trim();
   return foundFlag;
}

ossimString ossimPredatorKlvTable::valueAsString(ossimPredatorKlvIndex id, int set, int index)const

{
   ossimString result;
   if(valueAsString(result, id, set, index))
   {
      return result;
   }
   
   return ossimString("");
}

bool ossimPredatorKlvTable::getClassification(ossimString& classification)const
{
   bool result = false;
   classification = valueAsString(KLV_KEY_SECURITY_CLASSIFICATION);
   if (!classification.empty()) result = true;
   return result;
}

bool ossimPredatorKlvTable::getSecurityInformation(ossimString& si)const
{
   bool result = false;
   si = valueAsString(KLV_KEY_SECURITY_INFORMATION);
   if (!si.empty()) result = true;
   return result;
}

bool ossimPredatorKlvTable::getSensor(ossimString& sensor)const
{
   bool result = false;
   sensor = valueAsString(KLV_KEY_MISSION_NUMBER);
   if (!sensor.empty()) result = true;
   return result;
}

bool ossimPredatorKlvTable::getSensorFormat(ossimString& sensorFormat)const
{
   bool result = false;
   sensorFormat = valueAsString(KLV_KEY_IMAGE_SOURCE_SENSOR);
   if (!sensorFormat.empty()) result = true;
   return result;
}

bool ossimPredatorKlvTable::getCountryCode(ossimString& countryCode)const
{
   bool result = false;
   countryCode = valueAsString(KLV_KEY_OBJECT_COUNTRY_CODES);
   if (!countryCode.empty()) result = true;
   return result;
}

bool ossimPredatorKlvTable::getReleaseInstructions(ossimString& ri)const
{
   bool result = false;
   ri = valueAsString(KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS);
   if (!ri.empty()) result = true;
   return result;
}

bool ossimPredatorKlvTable::getNumberOfReportedTargets(ossim_uint32& targets)const
{
   bool result = false;
   ossimString targetsString = valueAsString(KLV_KEY_VMTI_NUMBER_REPORTED_TARGETS);
   if (!targetsString.empty())
   {
     targets = targetsString.toUInt32();
     result = true;
   }
   return result;
}

bool ossimPredatorKlvTable::getTargetID(ossim_uint32& targetid, ossim_uint32 index)const
{
   bool result = false;
   ossimString targetIDString = valueAsString(KLV_KEY_VMTI_VTARGET_PACK_ID, index);
   if (!targetIDString.empty())
   {
     targetid = targetIDString.toUInt32();
     result = true;
   }
   return result;
}

bool ossimPredatorKlvTable::getVMTITargetIntensity(ossim_uint32& targetIntensity, ossim_uint32 index)const
{
   bool result = false;
   ossimString targetIntensityString = valueAsString(KLV_KEY_VMTI_VTARGET_TARGET_INTENSITY);
   if (!targetIntensityString.empty())
   {
     targetIntensity = targetIntensityString.toUInt32();
     result = true;
   }
   return result;
}

bool ossimPredatorKlvTable::getVMTIFrameNumber(ossim_uint32& frameNumber)const
{
   bool result = false;
   ossimString frameNumberString = valueAsString(KLV_KEY_VMTI_MOTION_IMAGERY_FRAME_NUMBER);
   if (!frameNumberString.empty())
   {
     frameNumber = frameNumberString.toUInt32();
     result = true;
   }
   else frameNumber = 0;
   return result;
}

bool ossimPredatorKlvTable::getVMTIFrameWidth(ossim_uint32& frameWidth)const
{
   bool result = false;
   ossimString frameWidthString = valueAsString(KLV_KEY_VMTI_FRAME_WIDTH);
   if (!frameWidthString.empty())
   {
     frameWidth = frameWidthString.toUInt32();
     result = true;
   }
   else frameWidth = 0;
   return result;
}

bool ossimPredatorKlvTable::getVMTIFrameHeight(ossim_uint32& frameHeight)const
{
   bool result = false;
   ossimString frameHeightString = valueAsString(KLV_KEY_VMTI_FRAME_HEIGHT);
   if (!frameHeightString.empty())
   {
     frameHeight = frameHeightString.toUInt32();
     result = true;
   }
   else frameHeight = 0;
   return result;
}

bool ossimPredatorKlvTable::getVMTITargetCentroidPixelNumber(ossim_uint32& targetCentroidPixel, ossim_uint32 index)const
{
   bool result = false;
   ossimString targetCentroidPixelString = valueAsString(KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_NUMBER, index);
   if (!targetCentroidPixelString.empty())
   {
     targetCentroidPixel = targetCentroidPixelString.toUInt32();
     result = true;
   }
   else targetCentroidPixel = 0;
   return result;
}

bool ossimPredatorKlvTable::getVMTITopLeftPixelNumber(ossim_uint32& topLeftPixel, ossim_uint32 index)const
{
   bool result = false;
   ossimString topLeftPixelString = valueAsString(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_PIXEL_NUMBER, index);
   if (!topLeftPixelString.empty())
   {
     topLeftPixel = topLeftPixelString.toUInt32();
     result = true;
   }
   else topLeftPixel = 0;
   return result;
}

bool ossimPredatorKlvTable::getVMTIBottomRightPixelNumber(ossim_uint32& bottomRightPixel, ossim_uint32 index)const
{
   bool result = false;
   ossimString bottomRightPixelString = valueAsString(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_PIXEL_NUMBER, index);
   if (!bottomRightPixelString.empty())
   {
     bottomRightPixel = bottomRightPixelString.toUInt32();
     result = true;
   }
   else bottomRightPixel = 0;
   return result;
}

bool ossimPredatorKlvTable::getVMTIPointFromPixel(ossimDpt& point, ossim_uint32 index, ossim_uint32 pointtype)const
{
   ossim_uint32 pixel;
   ossim_uint32 frameWidth;
   getVMTIFrameWidth(frameWidth);
   switch (pointtype)
   {
     case 0:
       getVMTITargetCentroidPixelNumber(pixel, index);
       break;
     case 1:
       getVMTITopLeftPixelNumber(pixel, index);
       break;
     case 2:
       getVMTIBottomRightPixelNumber(pixel, index);
       break;
   }
   point.x = pixel % frameWidth;
   point.y = pixel / frameWidth;
}

bool ossimPredatorKlvTable::getVMTIUnixMicroTime(ossim_uint64& time)const
{
   bool result = false;
   ossimString unixMicroTimeString = valueAsString(KLV_KEY_UNIX_TIMESTAMP_RAW);  // Seems to be screwed up in VMTI, so using KLV frame time for now.  KLV_KEY_VMTI_PRECISION_TIME_STAMP_RAW);
   if (!unixMicroTimeString.empty())
   {
     time = unixMicroTimeString.toUInt64();
     result = true;
   }
   return result;
}

ossimString ossimPredatorKlvTable::getFootprintMetadata()
{
   ossimGpt ul, ur, ll, lr;
   getCornerPoints(ul, ur, lr, ll);
   ossimString polygon = "POLYGON((" 
                       +ossimString::toString(ul.lond())+" "
                       +ossimString::toString(ul.latd())+","
                       +ossimString::toString(ur.lond())+" "
                       +ossimString::toString(ur.latd())+","
                       +ossimString::toString(lr.lond())+" "
                       +ossimString::toString(lr.latd())+","
                       +ossimString::toString(ll.lond())+" "
                       +ossimString::toString(ll.latd())+","
                       +ossimString::toString(ul.lond())+" "
                       +ossimString::toString(ul.latd())+" "
                       +"))";

   ossimString result = "{";
   result+= "\"TIME\": \"" + valueAsString(KLV_KEY_UNIX_TIMESTAMP) + "\", "; 
   result+= "\"FOOTPRINT\": \"" + polygon + "\"}"; 
   return result;
}

ossimString ossimPredatorKlvTable::getSensorMetadata()
{
   ossim_float64 lat, lon, altitude;
   ossim_float32 heading, pitch, roll;
   getSensorPosition(lat, lon, altitude);
   getPlatformOrientation(heading, pitch, roll);
   ossimString point = "POINT("  
                       +ossimString::toString(lon)+" "
                       +ossimString::toString(lat)+","
                       +ossimString::toString(altitude)
                       +")";

   ossimString result = "{";
   result+= "\"TIME\": \"" + valueAsString(KLV_KEY_UNIX_TIMESTAMP) + "\", ";
   result+= "\"SENSOR_POSITION\": \"" + point + "\", "; 
   result+= "\"HEADING\": \"" + ossimString::toString(heading) + "\", ";
   result+= "\"PITCH\": \"" + ossimString::toString(pitch) + "\", ";
   result+= "\"ROLL\": \"" + ossimString::toString(roll) + "\"}";
   return result;
}

ossimString ossimPredatorKlvTable::getMetadata(ossim_int64 initialepoc)
{
   ossimGpt ul, ur, ll, lr;
   getCornerPoints(ul, ur, lr, ll);
   ossimString polygon = "POLYGON(("
                       +ossimString::toString(ul.lond())+" "
                       +ossimString::toString(ul.latd())+","
                       +ossimString::toString(ur.lond())+" "
                       +ossimString::toString(ur.latd())+","
                       +ossimString::toString(lr.lond())+" "
                       +ossimString::toString(lr.latd())+","
                       +ossimString::toString(ll.lond())+" "
                       +ossimString::toString(ll.latd())+","
                       +ossimString::toString(ul.lond())+" "
                       +ossimString::toString(ul.latd())+" "
                       +"))";
   ossim_float64 lat, lon, altitude;
   ossim_float32 heading, pitch, roll;
   getSensorPosition(lat, lon, altitude);
   getPlatformOrientation(heading, pitch, roll);
   ossimString point = "POINT("
                       +ossimString::toString(lon)+" "
                       +ossimString::toString(lat)+","
                       +ossimString::toString(altitude)
                       +")";
   ossim_int64 epoc;
   getUnixEpocTimestamp(epoc);
   ossim_float64 timeoffset = ( epoc - initialepoc) / 1000000.0;
   ossimString result = "{";
   result+= "\"TIMEOFFSET\": \"" + ossimString::toString(timeoffset) + "\", ";
   result+= "\"TIME\": \"" + valueAsString(KLV_KEY_UNIX_TIMESTAMP) + "\", ";
   result+= "\"FOOTPRINT\": \"" + polygon + "\", ";
   result+= "\"SENSOR_POSITION\": \"" + point + "\", ";
   result+= "\"HEADING\": \"" + ossimString::toString(heading) + "\", ";
   result+= "\"PITCH\": \"" + ossimString::toString(pitch) + "\", ";
   result+= "\"ROLL\": \"" + ossimString::toString(roll) + "\"}";
   return result;
}

bool ossimPredatorKlvTable::getCornerPoints(ossimGpt& pt1,
                                            ossimGpt& pt2,
                                            ossimGpt& pt3,
                                            ossimGpt& pt4)const
{
   bool result = false;
   klvMapType::const_iterator endIter = theKlvParameters.end();
   klvMapType::const_iterator lat1i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_1);
   klvMapType::const_iterator lat2i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_2);
   klvMapType::const_iterator lat3i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_3);
   klvMapType::const_iterator lat4i = theKlvParameters.find(KLV_KEY_CORNER_LATITUDE_POINT_4);
   klvMapType::const_iterator lon1i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_1);
   klvMapType::const_iterator lon2i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_2);
   klvMapType::const_iterator lon3i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_3);
   klvMapType::const_iterator lon4i = theKlvParameters.find(KLV_KEY_CORNER_LONGITUDE_POINT_4);
   

//std::cout << "TRIED FRO KEY: " << KLV_KEY_CORNER_LATITUDE_POINT_1 << std::endl;
//   std::cout << "END ITER? " << (lat1i==endIter) << std::endl;
   if((lat1i!=endIter)&&
      (lat2i!=endIter)&&
      (lat3i!=endIter)&&
      (lat4i!=endIter)&&
      (lon1i!=endIter)&&
      (lon2i!=endIter)&&
      (lon3i!=endIter)&&
      (lon4i!=endIter))
   {
      
      ossim_float64  lat1 = *reinterpret_cast<const ossim_float64*>(&(lat1i->second.theValue.front()));
      ossim_float64  lat2 = *reinterpret_cast<const ossim_float64*>(&(lat2i->second.theValue.front()));
      ossim_float64  lat3 = *reinterpret_cast<const ossim_float64*>(&(lat3i->second.theValue.front()));
      ossim_float64  lat4 = *reinterpret_cast<const ossim_float64*>(&(lat4i->second.theValue.front()));
      ossim_float64  lon1 = *reinterpret_cast<const ossim_float64*>(&(lon1i->second.theValue.front()));
      ossim_float64  lon2 = *reinterpret_cast<const ossim_float64*>(&(lon2i->second.theValue.front()));
      ossim_float64  lon3 = *reinterpret_cast<const ossim_float64*>(&(lon3i->second.theValue.front()));
      ossim_float64  lon4 = *reinterpret_cast<const ossim_float64*>(&(lon4i->second.theValue.front()));

      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat1);
         theEndian.swap(lat2);
         theEndian.swap(lat3);
         theEndian.swap(lat4);
         theEndian.swap(lon1);
         theEndian.swap(lon2);
         theEndian.swap(lon3);
         theEndian.swap(lon4);
         
      }
      pt1 = ossimGpt(lat1, lon1);
      pt2 = ossimGpt(lat2, lon2);
      pt3 = ossimGpt(lat3, lon3);
      pt4 = ossimGpt(lat4, lon4);
      
      result = true;
   }
   else
   {
      ossimDpt p1,p2,p3,p4;

      if(getFrameCenterOffsets(p1,p2,p3,p4))
      {
         ossim_float64 lat,lon,elevation;
         if(getFrameCenter(lat, lon, elevation))
         {
            pt1 = ossimGpt(lat+p1.lat, lon+p1.lon);
            pt2 = ossimGpt(lat+p2.lat, lon+p2.lon);
            pt3 = ossimGpt(lat+p3.lat, lon+p3.lon);
            pt4 = ossimGpt(lat+p4.lat, lon+p4.lon);
            result = true;
         }
      }
   }
   
   return result;
   
}

bool ossimPredatorKlvTable::getFrameCenterOffsets(ossimDpt& pt1Offset,
                                                   ossimDpt& pt2Offset,
                                                   ossimDpt& pt3Offset,
                                                   ossimDpt& pt4Offset)const
{
   bool result = false;
   klvMapType::const_iterator lat1i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_1);
   klvMapType::const_iterator lat2i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_2);
   klvMapType::const_iterator lat3i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_3);
   klvMapType::const_iterator lat4i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_4);
   klvMapType::const_iterator lon1i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_1);
   klvMapType::const_iterator lon2i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_2);
   klvMapType::const_iterator lon3i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_3);
   klvMapType::const_iterator lon4i = theKlvParameters.find(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_4);
   
   if((lat1i!=theKlvParameters.end())&&
      (lat2i!=theKlvParameters.end())&&
      (lat3i!=theKlvParameters.end())&&
      (lat4i!=theKlvParameters.end())&&
      (lon1i!=theKlvParameters.end())&&
      (lon2i!=theKlvParameters.end())&&
      (lon3i!=theKlvParameters.end())&&
      (lon4i!=theKlvParameters.end()))
   {
      ossim_float64  lat1 = *reinterpret_cast<const ossim_float64*>(&(lat1i->second.theValue.front()));
      ossim_float64  lat2 = *reinterpret_cast<const ossim_float64*>(&(lat2i->second.theValue.front()));
      ossim_float64  lat3 = *reinterpret_cast<const ossim_float64*>(&(lat3i->second.theValue.front()));
      ossim_float64  lat4 = *reinterpret_cast<const ossim_float64*>(&(lat4i->second.theValue.front()));
      ossim_float64  lon1 = *reinterpret_cast<const ossim_float64*>(&(lon1i->second.theValue.front()));
      ossim_float64  lon2 = *reinterpret_cast<const ossim_float64*>(&(lon2i->second.theValue.front()));
      ossim_float64  lon3 = *reinterpret_cast<const ossim_float64*>(&(lon3i->second.theValue.front()));
      ossim_float64  lon4 = *reinterpret_cast<const ossim_float64*>(&(lon4i->second.theValue.front()));
      
      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat1);
         theEndian.swap(lat2);
         theEndian.swap(lat3);
         theEndian.swap(lat4);
         theEndian.swap(lon1);
         theEndian.swap(lon2);
         theEndian.swap(lon3);
         theEndian.swap(lon4);
      }
      pt1Offset.lat = lat1;
      pt2Offset.lat = lat2;
      pt3Offset.lat = lat3;
      pt4Offset.lat = lat4;
      pt1Offset.lon = lon1;
      pt2Offset.lon = lon2;
      pt3Offset.lon = lon3;
      pt4Offset.lon = lon4;
      result = true;
   }

   return result;
}


bool ossimPredatorKlvTable::getFrameCenter(ossim_float64& lat,
                                           ossim_float64& lon,
                                           ossim_float64& elevation)const
{
   klvMapType::const_iterator lati  = theKlvParameters.find(KLV_KEY_FRAME_CENTER_LATITUDE);
   klvMapType::const_iterator loni  = theKlvParameters.find(KLV_KEY_FRAME_CENTER_LONGITUDE);
   klvMapType::const_iterator elevi = theKlvParameters.find(KLV_KEY_FRAME_CENTER_ELEVATION);
   
   if((lati != theKlvParameters.end())&&
      (loni != theKlvParameters.end()))
   {
      lat =  *reinterpret_cast<const ossim_float64*>(&(lati->second.theValue.front()));
      lon =  *reinterpret_cast<const ossim_float64*>(&(loni->second.theValue.front()));
      ossim_float32 elev = 0;
      if(elevi != theKlvParameters.end())
      {
         elev = *reinterpret_cast<const ossim_float32*>(&(elevi->second.theValue.front()));
         if(theNeedToSwapFlag)
         {
            theEndian.swap(elev);
         }
      }
      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat);
         theEndian.swap(lon);
      }
      elevation = elev;
      return true;
   }
   
   return false;
}

bool ossimPredatorKlvTable::getSensorPosition(ossim_float64& lat,
                                              ossim_float64& lon,
                                              ossim_float64& elevation)const
{
   klvMapType::const_iterator lati  = theKlvParameters.find(KLV_KEY_SENSOR_LATITUDE);
   klvMapType::const_iterator loni  = theKlvParameters.find(KLV_KEY_SENSOR_LONGITUDE);
   klvMapType::const_iterator elevi = theKlvParameters.find(KLV_KEY_SENSOR_TRUE_ALTITUDE);
   
   if((lati != theKlvParameters.end())&&
      (loni != theKlvParameters.end())&&
      (elevi != theKlvParameters.end()))
   {
      lat =  *reinterpret_cast<const ossim_float64*>(&(lati->second.theValue.front()));
      lon =  *reinterpret_cast<const ossim_float64*>(&(loni->second.theValue.front()));
      ossim_float32 elev = *reinterpret_cast<const ossim_float32*>(&(elevi->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(lat);
         theEndian.swap(lon);
         theEndian.swap(elev);
      }     
      elevation = elev;//*0.304801;
      return true;
   }
   
   return false;
}

bool ossimPredatorKlvTable::getPlatformOrientation(ossim_float32& heading,
                                                   ossim_float32& pitch,
                                                   ossim_float32& roll)const
{
   heading = valueAsString(KLV_KEY_PLATFORM_HEADING_ANGLE).toFloat32();
   ossimString pitchString = valueAsString(KLV_KEY_PLATFORM_PITCH_ANGLE);
   ossimString rollString = valueAsString(KLV_KEY_PLATFORM_ROLL_ANGLE);
   if (pitchString.empty()) pitchString = valueAsString(KLV_KEY_PLATFORM_PITCH_ANGLE_FULL);
   if (rollString.empty()) rollString = valueAsString(KLV_KEY_PLATFORM_ROLL_ANGLE_FULL);
   pitch = pitchString.toFloat32();
   roll = rollString.toFloat32();
   
   
   return true;
}

bool ossimPredatorKlvTable::getSensorRollAngle(ossim_float32& angle)const
{
   ossimString value = valueAsString(KLV_KEY_SENSOR_ROLL_ANGLE);
   if(!value.empty())
   {
      angle = value.toFloat32();
   }
   
   return !value.empty();
}

bool ossimPredatorKlvTable::getObliquityAngle(ossim_float32& angle)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_OBLIQUITY_ANGLE);
   angle = 0.0;
   if(value!=theKlvParameters.end())
   {
      angle =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(angle);
      }
   }
   
   return (value!=theKlvParameters.end());
}

bool ossimPredatorKlvTable::getSlantRange(ossim_float32& range)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_SLANT_RANGE);
   range = 0.0;
   if(value!=theKlvParameters.end())
   {
      range =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(range);
      }
   }
   
   return (value!=theKlvParameters.end());
   
}
bool ossimPredatorKlvTable::getHorizontalFieldOfView(ossim_float32& hfov)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_SENSOR_HORIZONTAL_FOV);
   hfov = 0.0;
   if(value!=theKlvParameters.end())
   {
      hfov =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(hfov);
      }
   }
   
   return (value!=theKlvParameters.end());
}

bool ossimPredatorKlvTable::getVerticalFieldOfView(ossim_float32& vfov)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_SENSOR_VERTICAL_FOV1);
   if(value == theKlvParameters.end())
   {
      value  = theKlvParameters.find(KLV_KEY_SENSOR_VERTICAL_FOV2);
   }
   vfov = 0.0;
   if(value!=theKlvParameters.end())
   {
      vfov =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(vfov);
      }
   }
   
   return (value!=theKlvParameters.end());
}

bool ossimPredatorKlvTable::getAngleToNorth(ossim_float32& angleToNorth)const
{
   klvMapType::const_iterator value  = theKlvParameters.find(KLV_KEY_ANGLE_TO_NORTH);
   angleToNorth = 0.0;
   if(value!=theKlvParameters.end())
   {
      angleToNorth =  *reinterpret_cast<const ossim_float32*>(&(value->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(angleToNorth);
      }
   }
   
   return (value!=theKlvParameters.end());
   
}

bool ossimPredatorKlvTable::getTargetWidthInMeters(ossim_float32& targetWidth)const
{
   ossimString value = valueAsString(KLV_KEY_TARGET_WIDTH);
   
   targetWidth = value.toFloat32();
   
   return !value.empty();
}

ossimString ossimPredatorKlvTable::getUtcTimestamp()const
{
   return valueAsString(KLV_KEY_VIDEO_START_DATE_TIME_UTC);
}


bool ossimPredatorKlvTable::getUnixEpocTimestamp(ossim_int64& timestamp)const
{
   klvMapType::const_iterator timei  = theKlvParameters.end();//theKlvParameters.find(KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970);
   if(timei == theKlvParameters.end())
   {
      timei  = theKlvParameters.find(KLV_KEY_UNIX_TIMESTAMP);
   }
   if(timei == theKlvParameters.end())
   {
      timei = theKlvParameters.find(KLV_KEY_USER_DEFINED_TIMESTAMP_MICROSECONDS_1970);
   }
   if(timei != theKlvParameters.end())
   {
      timestamp =  *reinterpret_cast<const ossim_uint64*>(&(timei->second.theValue.front()));
      if(theNeedToSwapFlag)
      {
         theEndian.swap(timestamp);
      }
      return true;
   }
   
   return false;
}

bool ossimPredatorKlvTable::getUnixEpocTimestampInSeconds(ossim_int64& seconds,
                                                          ossim_float64& fractionalPart)const
{
   ossim_int64 epocInMicroseconds;
   bool result = getUnixEpocTimestamp(epocInMicroseconds);
   ossim_float64 fractionalSeconds = static_cast<ossim_float64>(epocInMicroseconds*1e-6);
   seconds = static_cast<ossim_uint64>(fractionalSeconds);
   fractionalPart = fractionalSeconds - seconds;
   
   return result;
}

bool ossimPredatorKlvTable::getUnixEpocTimestampInFractionalSeconds(ossim_float64& fractionalSeconds)const
{
   ossim_int64 epocInMicroseconds;
   bool result = getUnixEpocTimestamp(epocInMicroseconds);
   fractionalSeconds = static_cast<ossim_float64>(epocInMicroseconds/10e-6);
   
   return result;
}

bool ossimPredatorKlvTable::getDate(ossimDate& d, bool shiftToGmtZero)const
{
   bool result = getDateUsingUtc(d, shiftToGmtZero);
   
   if(!result)
   {
      result = getDateUsingEpoc(d);
   }
   return result;
}

bool ossimPredatorKlvTable::getDateUsingEpoc(ossimDate& d)const
{
   bool result = false;
   ossim_int64 t;
   ossim_float64 fraction=0;
   
   if(getUnixEpocTimestampInSeconds(t, fraction))
   {
      result = true;
      d.setTimeNoAdjustmentGivenEpoc(t);
      d.setFractionalSecond(fraction);
   }
   
   return result;
}

bool ossimPredatorKlvTable::getDateUsingUtc(ossimDate& d, bool shiftToGmtZero)const
{
   bool result = false;
   ossimString utc = getUtcTimestamp();
   if(utc.size() > 0)
   {
      result = d.setIso8601(utc, shiftToGmtZero);
   }
   return result;
}

int ossimPredatorKlvTable::findPredatorKlvIndex(const ossim_uint8* buf)const
{
   ossim_int32 idx = 0;
   

   while(OSSIM_PREDATOR_UDS_TABLE[idx].theId != -1)
   {
      if(std::equal(buf,
                    buf+16,
                    OSSIM_PREDATOR_UDS_TABLE[idx].theKey))
      {
         return idx;
      }
      ++idx;
   }
   
   return -1;
}

int ossimPredatorKlvTable::findPredatorKlvIndexByKey(ossim_uint32 key)const
{
   ossim_int32 idx = 0;
   

   while(OSSIM_PREDATOR_UDS_TABLE[idx].theId != -1)
   {
      if(key == OSSIM_PREDATOR_UDS_TABLE[idx].theId)
      {
        return idx;
      }
      ++idx;
   }
   
   return -1;
}

void ossimPredatorKlvTable::loadVariableDataNullTerminated(std::vector<ossim_uint8>& result, 
                                                           const std::vector<ossim_uint8>& buf, 
                                                           ossim_uint32& idx)const
{
   while((idx < buf.size())&&(buf[idx] != '\0'))
   {
      result.push_back(buf[idx]);
      ++idx;
   }
   if(idx < buf.size())
   {
      ++idx;
   }
}


void ossimPredatorKlvTable::addSecurityMetadataLocalSetElements(const std::vector<ossim_uint8>& buffer, klvMapType& tempTable)
{
   //std::cout << "addSecurityMetadataLocalSetElements: ....................... entered\n";
   if(buffer.size() == 0) return;
   ossim_uint32 idx = 0;
   bool done = false;
   while(!done&&((idx+2) < buffer.size()))
   {
      ossim_uint32 key    = buffer[idx++];
      ossim_uint32 length = buffer[idx++];
      if(length > 0)
      {
        switch(key)
        {
           case 1:
           {
              ossim_uint8 classification = (ossim_uint8)(*(buffer.begin()+idx));
              ossimString value;
              switch(classification)
              {
              }

              Node n(KLV_KEY_SECURITY_CLASSIFICATION,
                     std::vector<ossim_uint8>(value.begin(), value.end()));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 2://Classifying Country and Releasing Instructions Country Coding Method
           {
              Node n(KLV_KEY_CLASSIFYING_COUNTRY_AND_RELEASE_INSTRUCTIONS_COUNTRY_CODING_METHOD,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              break;
           }
           case 3://Classifying Country
           {
              if(traceDebug())  std::cout << "Classifying Country Not Handled: " << std::endl;
              break;
           }
           case 4://Security information
	   {
              Node n(KLV_KEY_SECURITY_INFORMATION,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
 	   }
           case 5://Caveats
	   {
              Node n(KLV_KEY_SECURITY_CAVEATS,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 6://Releasing Instructions
           {
              Node n(KLV_KEY_SECURITY_RELEASE_INSTRUCTIONS,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 7://Classified By
           {
              Node n(KLV_KEY_CLASSIFIED_BY,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 8://Derived From
           {
              Node n(KLV_KEY_DERIVED_FROM,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 9://Classification Reason
           {
              Node n(KLV_KEY_CLASSIFICATION_REASON,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 10://Declassification Date
           {
              Node n(KLV_KEY_DECLASSIFICATION_DATE,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 11://Classification and Marking System
           {
              Node n(KLV_KEY_CLASSIFICATION_AND_MARKING_SYSTEM,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 12://Object Country Coding Method
           {
              Node n(KLV_KEY_OBJECT_COUNTRY_CODING_METHOD,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;


             break;
           }
           case 13://Object Country Codes
           {
              Node n(KLV_KEY_OBJECT_COUNTRY_CODES,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 14://Classification Comments
           {
              Node n(KLV_KEY_CLASSIFICATION_COMMENT,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 15://UMID1 Video
           {
              Node n(KLV_KEY_UMID1,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 16://UMID2 Audio
           {
              Node n(KLV_KEY_UMID2,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 17://UMID3 Data
           {
              Node n(KLV_KEY_UMID3,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 18://UMID4 System
           {
              Node n(KLV_KEY_UMID4,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 19://Stream ID
           {
              Node n(KLV_KEY_STREAM_ID,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 20://Transport Stream ID
           {
              Node n(KLV_KEY_TRANSPORT_STREAM_ID,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 21://Item Designator ID
           {
              Node n(KLV_KEY_ITEM_DESIGNATOR_ID,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 22://
           {
              Node n(KLV_KEY_SECURITY_VERSION,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 23://
           {
              Node n(KLV_KEY_CLASSIFYING_COUNTRY_AND_RELEASING_INSTRUCTIONS_COUNTRY_CODE_METHOD_VERSION_DATE,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 24://
           {
              Node n(KLV_KEY_OBJECT_COUNTRY_CODING_METHOD_VERSION_DATE,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           default:
           {
              if(traceDebug()) std::cout << "SECURITY KEY " << key << " Not handled\n";
	      std::cout << "SECURITY KEY " << key << " Not handled\n";
              break;
           }
        }
      }
      idx +=length;
   }
}

void ossimPredatorKlvTable::addVMTILocalDataSetElements(const std::vector<ossim_uint8>& buffer, klvMapType& tempTable)
{
   if(buffer.size() == 0) return;
   //printHex(buffer);
   ossim_uint32 idx = 0;
   bool done = false;
   while(!done&&((idx+2) < buffer.size()))
   {
      ossim_uint32 key = lds_decode_key(&buffer[0], idx);
      ossim_uint32 length= klv_decode_length(&buffer[0], idx);
      //ossim_uint32 key    = buffer[idx++];
      //ossim_uint32 length = buffer[idx++];
      if(length > 0)
      {
        switch(key)
        {
           case 2: // unix timestamp
           {
              ossim_uint64 value = *reinterpret_cast<const ossim_uint64*>(&buffer.front()+idx);
              //valueToString already swaps this, so it was getting swapped twice
              //if(theNeedToSwapFlag)
              //{
              //  theEndian.swap(value);
              //}
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
	      ossim_uint8* tempBuf2 = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_PRECISION_TIME_STAMP,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              Node n2(KLV_KEY_VMTI_PRECISION_TIME_STAMP_RAW,
                     std::vector<ossim_uint8>(tempBuf2,
                                              tempBuf2+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n2.theId),
                                                     n2));
              break;
           }
	   case 3://System Name/Description (string)
           {
              Node n(KLV_KEY_VMTI_SYSTEM_NAME,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 4://LS Version Number (uint16)
           {
              ossim_uint16 value = 0;
              ossim_uint32 idx2 = 0;
              while (idx2 < length)
              {
                value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                ++idx2;
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_LS_VERSION_NUMBER,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+2));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 5://Total Number of Targets Detected in the frame 
           {
	      ossim_uint32 value = 0;
	      ossim_uint32 idx2 = 0;
	      while (idx2 < length)
	      {
		value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
		++idx2;
	      }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_TOTAL_TARGETS_DETECTED,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 6://Number of Reported Targets 
           {
              ossim_uint32 value = 0;
              ossim_uint32 idx2 = 0;
              while (idx2 < length)
              {
                value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                ++idx2;
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_NUMBER_REPORTED_TARGETS,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              break;
           }
           case 7://Motion Imagery Frame Number 
           {
              ossim_uint32 value = 0;
              ossim_uint32 idx2 = 0;
              while (idx2 < length)
              {
                value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                ++idx2;
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_MOTION_IMAGERY_FRAME_NUMBER,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              break;
           }
           case 8://Frame Width
           {
              ossim_uint32 value = 0;
              ossim_uint32 idx2 = 0;
              while (idx2 < length)
              {
                value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                ++idx2;
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_FRAME_WIDTH,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              break;
           }
           case 9://Frame Height
           {
              ossim_uint32 value = 0;
              ossim_uint32 idx2 = 0;
              while (idx2 < length)
              {
                value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                ++idx2;
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_VMTI_FRAME_HEIGHT,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              break;
           }
           case 10:
           {
              Node n(KLV_KEY_VMTI_SOURCE_SENSOR,
                     std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
	   case 101:
	   {
              std::vector<ossim_uint8> tempBuf(buffer.begin()+idx, buffer.begin()+idx+length);
		//printHex(tempBuf);
              addVTargetSeries(tempBuf, tempTable);
              break;
           }
           default:
           {
              //if(traceDebug()) 
              std::cout << "VMTI LOCAL DATA SET KEY " << key << " Not handled\n";
              break;
           }
        }
      }
      idx +=length;
   }
}

void ossimPredatorKlvTable::addVTargetSeries(const std::vector<ossim_uint8>& buffer, klvMapType& tempTable)
{
   if(buffer.size() == 0) return;
   ossim_uint32 idx = 0;
   ossim_uint32 packnum = 0;
   while((idx+2) < buffer.size())
   {
      //ossim_uint32 key = lds_decode_key(&buffer[0], idx);
      // NO KEY HERE - k-lvlvlvlv just a bunch of lengths and values for the target packs
      ossim_uint32 length2= klv_decode_length(&buffer[0], idx);
      //std::cout << "VTARGET PACK LENGTH: " << ossimString::toString(length2) << std::endl;
      if(length2 > 0)
      {
	ossim_uint32 offset = idx;
	// Decode the Target Pack
	ossim_uint32 targetid = lds_decode_key(&buffer[0], idx);
        ossim_uint8* targetBuf = reinterpret_cast<ossim_uint8*>(&targetid);
        Node n(KLV_KEY_VMTI_VTARGET_PACK_ID,
                       std::vector<ossim_uint8>(targetBuf,
                                                targetBuf+4), packnum);
        tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));

	while(((idx-offset)+2) < length2)
	{
	  ossim_uint32 key = lds_decode_key(&buffer[0], idx);
	  ossim_uint32 length= klv_decode_length(&buffer[0], idx);

	  if (length > 0)
	  {
	    switch(key)
            {
              case 1:
              {
                ossim_uint64 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_NUMBER,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 2:
              {
                ossim_uint64 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_PIXEL_NUMBER,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 3:
              {
                ossim_uint64 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_PIXEL_NUMBER,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 4:
              {
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_PRIORITY,
                   std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
                break;
              }
              case 5:
              {
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_CONFIDENCE_LEVEL,
                   std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
                break;
              }
              case 6:
              {
                ossim_uint16 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_NEW_DETECTION_FLAG_TARGET_HISTORY,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+2), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 7:
              {
                Node n(KLV_KEY_VMTI_VTARGET_PERCENTAGE_OF_TARGET_PIXELS,
                   std::vector<ossim_uint8>(buffer.begin()+idx, buffer.begin()+(idx+length)), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
                break;
              }
              case 8:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_COLOR,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+4), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 9:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_INTENSITY,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+4), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 10:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }

                ossim_float64 newvalue  = mapValue(value, 0, 16777215, -19.2, 19.2);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(newvalue);
                }

                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&newvalue);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_LOCATION_LATITUDE_OFFSET,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 11:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_float64 newvalue  = mapValue(value, 0, 16777215, -19.2, 19.2);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(newvalue);
                }

                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&newvalue);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_LOCATION_LONGITUDE_OFFSET,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 12:
              {
                ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(buf);
                }
                ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(value);
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_HEIGHT,//KLV_KEY_SENSOR_TRUE_ALTITUDE,
                       std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
             }
              case 13:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_float64 newvalue  = mapValue(value, 0, 16777215, -19.2, 19.2);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(newvalue);
                }

                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&newvalue);
                Node n(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_LATITUDE_OFFSET,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 14:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_float64 newvalue  = mapValue(value, 0, 16777215, -19.2, 19.2);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(newvalue);
                }

                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&newvalue);
                Node n(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_TOP_LEFT_LONGITUDE_OFFSET,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 15:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_float64 newvalue  = mapValue(value, 0, 16777215, -19.2, 19.2);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(newvalue);
                }

                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&newvalue);
                Node n(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_LATITUDE_OFFSET,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 16:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_float64 newvalue  = mapValue(value, 0, 16777215, -19.2, 19.2);
                if(theNeedToSwapFlag)
                {
                  theEndian.swap(newvalue);
                }

                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&newvalue);

                Node n(KLV_KEY_VMTI_VTARGET_BOUNDING_BOX_BOTTOM_RIGHT_LONGITUDE_OFFSET,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+8), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 18:
              {
                std::vector<ossim_uint8> tempBuf(buffer.begin()+idx, buffer.begin()+idx+length);
                //printHex(tempBuf);
                addBoundarySeries(tempBuf, tempTable, packnum);
                break;
              }
              case 19:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_ROW,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+4), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
              case 20:
              {
                ossim_uint32 value = 0;
                ossim_uint32 idx2 = 0;
                while (idx2 < length)
                {
                  value = (value << 8) | *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx+idx2);
                  ++idx2;
                }
                ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
                Node n(KLV_KEY_VMTI_VTARGET_TARGET_CENTROID_PIXEL_COLUMN,
                       std::vector<ossim_uint8>(tempBuf,
                                                tempBuf+4), packnum);
                tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                       n));
                break;
              }
	      default:
	        std::cout << "VTARGET PACK NUMBER: " << ossimString::toString(packnum) << " ID: " << ossimString::toString(targetid) << " KEY: " << ossimString::toString(key) << " WITH LENGTH " << ossimString::toString(length) << " NOT HANDLED" << std::endl;
	        break;
            }
	    idx +=length;
	  }
	}
      }
      ++packnum;
   }
}

void ossimPredatorKlvTable::addBoundarySeries(const std::vector<ossim_uint8>& buffer, klvMapType& tempTable, int packnum)
{
   if(buffer.size() == 0) return;
   //printHex(buffer);
   ossim_uint32 idx = 0;
   ossim_uint32 locationnum = 0;
   while((idx+2) < buffer.size())
   {
      ossim_uint32 length= klv_decode_length(&buffer[0], idx);

      if (length > 10) // current test data only has lat/lon/height 
      { 
	      // LATITUDE
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n1(KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_LATITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8), packnum, locationnum);
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n1.theId),
                                                     n1));
	      idx+=4;

              // LONGITUDE
              // Map -(2^31-1)..(2^31-1) to +/-90
              buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n2(KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_LONGITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8), packnum, locationnum);
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n2.theId),
                                                     n2));
	      idx+=4;

              // HEIGHT
              ossim_uint16 buf2 = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf2);
              }
              value  = mapValue(buf2, 0, 65535, -900, 19000);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n3(KLV_KEY_VMTI_VTARGET_BOUNDARY_LOCATION_HEIGHT,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8), packnum, locationnum);
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n3.theId),
                                                     n3));
	      idx+=2;
	      ++locationnum;
      } 
   }
}

//#include <ossim/base/ossimTraceManager.h>
void ossimPredatorKlvTable::addUasDatalinkLocalDataSet(const std::vector<ossim_uint8>& buffer, klvMapType& tempTable, ossim_uint16& checksum)
{
 

//   ossimTraceManager::instance()->setTracePattern("ossimPredatorKlvTable.*");
//   if (traceDebug()) std::cout << "ossimPredatorKlvTable::addUasDatalinkLocalDataSet: entered....................\n";
   if(buffer.size() == 0) return;
   ossim_uint32 idx = 0;
   bool done = false;
   while(!done&&((idx+2) < buffer.size()))
   {
      ossim_uint32 key = lds_decode_key(&buffer[0], idx);
      //ossim_uint32 key= buffer[idx++];
      //ossim_uint32 length= buffer[idx++];
      ossim_uint32 length= klv_decode_length(&buffer[0], idx);
      //std::cout << "KEY ====================== " << key << std::endl;
      //std::cout << "LENGTH ====================== " << length << std::endl;
      if(length > 0)
      {
        switch(key)
        {
           case 1: // checksum
           {
              //std::cout << "CHECKSUM\n";
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              checksum = buf;
              break;
           }
           case 2: // unix timestamp
           {
              ossim_uint64 value = *reinterpret_cast<const ossim_uint64*>(&buffer.front()+idx);
	      //valueToString already swaps this, so it was getting swapped twice
              //if(theNeedToSwapFlag)
              //{
              //  theEndian.swap(value);
              //}
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_UNIX_TIMESTAMP,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              Node n2(KLV_KEY_UNIX_TIMESTAMP_RAW,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n2.theId),
                                                     n2));
              
              break;
           }
           case 3:
           {
              Node n(KLV_KEY_MISSION_NUMBER,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              //std::cout << "MISSION ID!!" << std::endl;
              break;
           }
           case 4:
           {
              Node n(KLV_KEY_PLATFORM_TAIL_NUMBER,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              //std::cout << "PLATFORM TAIL!! " << valueAsString(KLV_KEY_PLATFORM_TAIL_NUMBER) << std::endl;
              break;
           }
           case 5:
           {
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 heading  = mapValue(buf, 0.0, (1<<16) - 1, 0.0, 360.0);
              //std::cout << "HEADING == " << heading << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(heading);
              }

              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&heading);
              Node n(KLV_KEY_PLATFORM_HEADING_ANGLE,
                  std::vector<ossim_uint8>(tempBuf,
                                           tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),n));
              //            std::cout << "PLATFORM HEADING!!" << std::endl;
              break;
           }
           case 6:
           {
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -((1<<15)-1), ((1<<15)-1), -20,20);//20.0*(buf)/(double)((1<<15) - 1);
              //std::cout << "PITCH == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_PLATFORM_PITCH_ANGLE,
                  std::vector<ossim_uint8>(tempBuf,
                                           tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),n));
             //            std::cout << "PLATFORM PITCH!!" << std::endl;
              break;
           }
           case 7:
           {
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              double value  = mapValue(buf, -((1<<15)-1), ((1<<15)-1), -50,50);
              //std::cout << "ROLL == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_PLATFORM_ROLL_ANGLE,
                  std::vector<ossim_uint8>(tempBuf,
                                           tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),n));
              //            std::cout << "PLATFORM ROLL!!" << std::endl;
              break;
           }
           case 8:
           {
             //ossim_uint8 buf = *reinterpret_cast<const ossim_uint8*>(&buffer.front()+idx);
              
              if(traceDebug()) std::cout << "PLATFORM TRUE AIRSPEED not handled!!" << std::endl;
              break;
           }
           case 9:
           {
              Node n(KLV_KEY_INDICATED_AIR_SPEED,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              //if(traceDebug()) std::cout << "PLATFORM INDICATED AIRSPEED!!" << std::endl;
              break;
           }
           case 10:
           {
              Node n(KLV_KEY_PLATFORM_DESIGNATION,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              //std::cout << "PLATFORM DESIGNATION: " << valueAsString(KLV_KEY_PLATFORM_DESIGNATION) << std::endl;
              //if(traceDebug()) std::cout << "PLATFORM DESIGNATION not handled!!" << std::endl;
              break;
           }
           case 11: // KLV_KEY_IMAGE_SOURCE_SENSOR
           {
              Node n(KLV_KEY_IMAGE_SOURCE_SENSOR,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
             // std::cout << "IMAGE SOURCE SENSOR!!" << valueAsString(KLV_KEY_IMAGE_SOURCE_SENSOR).trim()<< std::endl;
              break;
           }
           case 12:
           {
              Node n(KLV_KEY_IMAGE_COORDINATE_SYSTEM,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              //std::cout << "IMAGE COORDINATE SYSTEM!!" << std::endl;
              break;
           }
           case 13://KLV_KEY_SENSOR_LATITUDE
           {
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }

              // Map -(2^31-1)..(2^31-1) to +/-90.
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90, 90);//(360.0*(((double)buf + 2147483647.0)/(4294967294.0)))-180.0; //180.0*((buf)/(double)((ossim_int64)(1<<31) - 1));
              //std::cout << "LAT == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_LATITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              //            std::cout << "SENSOR LAT!!" << std::endl;
              break;
           }
           case 14://KLV_KEY_SENSOR_LONGITUDE
           {
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              //KLV_KEY_SENSOR_LONGITUDE
              // Map -(2^31-1)..(2^31-1) to +/-180.
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180, 180); //180.0*((buf)/(double)((ossim_int64)(1<<31) - 1));
              //std::cout << "LON == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_LONGITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              //            std::cout << "SENSOR LON!!" << std::endl;
              break;
           }
           case 15://KLV_KEY_SENSOR_TRUE_ALTITUDE
           {
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000); 
              //std::cout << "ALTITUDE == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_TRUE_ALTITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
  //            std::cout << "SENSOR TRUE ALTITUDE!!" << std::endl;
              break;
           }
           case 16://KLV_KEY_SENSOR_HORIZONTAL_FOV
           {
              // map -2^16-1..2^16-1 to 0..180
             ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float32 value  = mapValue(buf, 0, 65535, 0, 180); 
              //std::cout << "HFOV == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_HORIZONTAL_FOV,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              //            std::cout << "SENSOR HORIZONTAL FOV!!" << std::endl;
              break;
           }
           case 17://KLV_KEY_SENSOR_VERTICAL_FOV1
           {
              // Map 0..(2^16-1) to 0..180.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float32 value  = mapValue(buf, 0, 65535, 0, 180); 
              //std::cout << "VFOV == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_VERTICAL_FOV1,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 18://KLV_KEY_SENSOR_RELATIVE_AZIMUTH_ANGLE
           {
              // Map 0..(2^32-1) to 0..360.
              ossim_uint32 buf = *reinterpret_cast<const ossim_uint32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 4294967295, 0, 360); 
              //std::cout << "REALATIVE AZIMUTH == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_RELATIVE_AZIMUTH_ANGLE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
             //            std::cout << "SENSOR REALTIVE AZIMUTH ANGLE!!" << std::endl;
              break;
           }
           case 19://KLV_KEY_SENSOR_RELATIVE_ELEVATION_ANGLE
           {
              //Map -(2^31-1)..(2^31-1) to +/-180.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647.0,2147483647.0,-180.0,180.0);
              //std::cout << "REALATIVE Elevation == " << value << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_RELATIVE_ELEVATION_ANGLE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 20: //KLV_KEY_SENSOR_RELATIVE_ROLL_ANGLE
           {
              //0..(2^32-1) to 0..360.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 4294967295, 0, 360); 
              //std::cout << "REALATIVE roll == " << value << std::endl;
              //            std::cout << "SENSOR REALTIVE ROLL ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_RELATIVE_ROLL_ANGLE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 21: // KLV_KEY_SLANT_RANGE
           {
              // Map 0..(2^32-1) to 0..5000000
              ossim_uint32 buf = *reinterpret_cast<const ossim_uint32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 4294967295, 0, 5000000); 
              //std::cout << "SLANT range == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SLANT_RANGE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 22: //KLV_KEY_TARGET_WIDTH
           {
              //Map 0..(2^16-1) to 0..10000
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float32 value  = mapValue(buf, 0, 65535, 0, 10000); 
              //std::cout << "TARGET width == " << value << std::endl;
              //            std::cout << "TARGET WIDTH!!" << std::endl;
               if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_TARGET_WIDTH,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+4));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 23:
           {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0); 
              //std::cout << "FRAME CENTER LAT == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_FRAME_CENTER_LATITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 24:
           {
              // Map -(2^31-1)..(2^31-1) to +/-180
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180.0, 180.0); 
              //std::cout << "FRAME CENTER LON == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_FRAME_CENTER_LONGITUDE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 25:
           {
             // Map 0..(2^16-1) to -900..19000
              ossim_uint16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000); 
              //std::cout << "FRAME CENTER ELEV == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_FRAME_CENTER_ELEVATION,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 26: 
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_1,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 27:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //std::cout << "offset corner lon 1 == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_1,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 28:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //std::cout << "offset corner lat 2 == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_2,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 29:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //std::cout << "offset corner lon 2 == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_2,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 30:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //std::cout << "offset corner lat 3 == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_3,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 31:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //std::cout << "offset corner lon 3 == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_3,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 32:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //std::cout << "offset corner lat 4 == " << value << std::endl;
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_4,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 33:
           {
              // Map -(2^15-1)..(2^15-1) to +/-0.075.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -0.075, 0.075); 
              //            std::cout << "SENSOR SLANT ANGLE!!" << std::endl;
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_4,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 34:
           {
              if(traceDebug()) std::cout << "ICING DETECTED Not Handled!!" << std::endl;
              break;
           }
           case 35:
           {
              if(traceDebug()) std::cout << "WIND DIRECTION Not Handled!!" << std::endl;
              break;
           }
           case 36:
           {
              if(traceDebug())  std::cout << "WIND SPEED not handled!!" << std::endl;
              break;
           }
           case 37://KLV_KEY_STATIC_PRESSURE
           {
              // Map 0..(2^16-1) to 0..5000 mbar.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_uint16 value  = mapValue(buf, 0, 65535, 0, 5000); 
              
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_STATIC_PRESSURE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+2));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));


           //   if(traceDebug()) std::cout << "Static Pressure not handled!!" << std::endl;
              break;
           }
           case 38:
           {
              if(traceDebug()) std::cout << "DENSITY ALTITUDE not handled!!" << std::endl;
              break;
           }
           case 39:
           {
              if(traceDebug()) std::cout << "OUTSIDE AIR TEMP not handled!!" << std::endl;
              break;
           }
           case 40:
           {
              if(traceDebug()) std::cout << "Target Location Latitude not handled!!" << std::endl;
              break;
           }
           case 41:
           {
              if(traceDebug()) std::cout << "Target Location Longitude not handled!!" << std::endl;
              break;
           }
           case 42:
           {
              if(traceDebug()) std::cout << "Target Location Elevation not handled!!" << std::endl;
              break;
           }
           case 43:
           {
              if(traceDebug()) std::cout << "Target track gate width not handled!!" << std::endl;
              break;
           }
           case 44:
           {
              if(traceDebug()) std::cout << "Target track gate height not handled!!" << std::endl;
              break;
           }
           case 45:
           {
              if(traceDebug()) std::cout << "Target Error esitimate CE90 not handled!!" << std::endl;
              break;
           }
           case 46:
           {
              if(traceDebug())
              {
                 std::cout << "Target Error esitimate LE90!!" << std::endl;
              }
              break;
           }
           case 47:
           {
              Node n(KLV_KEY_GENERIC_FLAG_DATA_01,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));

              //std::cout << "Generic Flag Data 01!!" << (int)((buffer.front()+idx)) << std::endl;
              break;
           }
           case 48:
           {
              std::vector<ossim_uint8> tempBuf(buffer.begin()+idx, buffer.begin()+idx+length);
              addSecurityMetadataLocalSetElements(tempBuf, tempTable);
              break;
           }
           case 49:
           {
              if(traceDebug())
              {
                 std::cout << "Differential pressure!!" << std::endl;
              }
              break;
           }
           case 50:
           {
              if(traceDebug())
              {
                 std::cout << "Platform angle of attack!!" << std::endl;
              }
              break;
           }
           case 51:
           {
              if(traceDebug())
              {
                 std::cout << "Platform vertical speed!!" << std::endl;
              }
              break;
           }
           case 52:
           {
              if(traceDebug())
              {
                 std::cout << "Platform side slip angle!!" << std::endl;
              }
              break;
           }
           case 53:
           {
              if(traceDebug())
              {
                 std::cout << "airfilled barometrc pressure!!" << std::endl;
              }
              // airfiled barometrc pressure
              break;
           }
           case 54:
           {
              if(traceDebug())
              {
                 std::cout << "airfiled elevation!! Not handled" << std::endl;
              }
              // airfiled elevation
              break;
           }
           case 55:
           {
              if(traceDebug())
              {
                 std::cout << "relative humidity!! Not handled" << std::endl;
              }
              // relative humidity
              break;
           }
           case 56://KLV_KEY_PLATFORM_GROUND_SPEED
           {
              Node n(KLV_KEY_PLATFORM_GROUND_SPEED,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              // platform ground speed
              break;
           }
           case 57:
           {
              if(traceDebug())
              {
                 std::cout << "ground range!! Not handled" << std::endl;
              }
              // ground range
              break;
           }
           case 58:
           {
              if(traceDebug())
              {
                 std::cout << " platform fuel remaining! Not handled" << std::endl;
              }
              // platform fuel remaining
              break;
           }
           case 59:
           {
              if(traceDebug())
              {
                 std::cout << "platform call sign! Not handled" << std::endl;
              }
             // platform call sign
              break;
           }
           case 60:
           {
              if(traceDebug())
              {
                 std::cout << "weapon load! Not handled" << std::endl;
              }
             // weapon load
              break;
           }
           case 61:
           {
              if(traceDebug())
              {
                  std::cout << "weapon fired Not Handled!" << std::endl;
              }
              // weapon fired
              break;
           }
           case 62:
           {
              if(traceDebug())
              {
                 std::cout << "Laser PRF Code Not handled" << std::endl;
              }
              // Laser PRF Code
              break;
           }
           case 63:
           {
              if(traceDebug())
              {
                 std::cout << "Sensor Field of View Name Not handled" << std::endl;
              }
             //Sensor Field of View Name
              break;
           }
           case 64:// KLV_KEY_PLATFORM_MAGNETIC_HEADING_ANGLE
           {
              // Map 0..(2^16-1) to 0..360.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 65535, 0, 360); 
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_PLATFORM_MAGNETIC_HEADING_ANGLE,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
             //            std::cout << "SENSOR REALTIVE AZIMUTH ANGLE!!" << std::endl;
             // platform magnetic heading
              break;
           }
           case 65:// KLV_KEY_UAS_LDS_VERSION_NUMBER
           {
              Node n(KLV_KEY_UAS_LDS_VERSION_NUMBER,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              //std::cout << "KLV_KEY_UAS_LDS_VERSION_NUMBER: " << valueAsString(KLV_KEY_UAS_LDS_VERSION_NUMBER) <<std::endl;
              // UAS LDS Version Number
              break;
           }
           case 66:
           {
              if(traceDebug()) std::cout << "target location covariance matrix  Not handled" << std::endl;
             // target locatio covariance matrix
              break;
           }
           case 67:
           {
              // alternate platform latitude
              if(traceDebug()) std::cout << " alternate platform latitude No Handled!"  << std::endl;  
              break;
           }
           case 68:
           {
                 if(traceDebug()) std::cout << "alternate platform longitude Not Handled! "  <<key  << std::endl;  
             // alternate platform longitude
              break;
           }
           case 69:
           {
              // alternate platform altitude
                if(traceDebug())  std::cout << "alternate platform altitude Not handled "  <<key  << std::endl;  
             break;
           }
           case 70:
           {
              // alternate platform name
               if(traceDebug()) std::cout << "alternate platform name Not handled "  <<key  << std::endl;  
             break;
           }
           case 71:
           {
              // alternate platform heading
              if(traceDebug()) std::cout << "alternate platform heading Not handled "  <<key  << std::endl;  
              break;
           }
           case 72:
           {
              if(traceDebug()) std::cout << "EVENT START TIME  Not handled "  <<key  << std::endl;  
  //            std::cout << "EVENT START TIME!!" << std::endl;
              break;
           }
	   case 74:
	   {
              std::vector<ossim_uint8> tempBuf(buffer.begin()+idx, buffer.begin()+idx+length);
              addVMTILocalDataSetElements(tempBuf, tempTable);
              break;
	   }
	   case 75:
	   {
              // Map 0..(2^16-1) to -900..19000.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_ELLIPSOID_HEIGHT,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
	   }
           case 77:
           {
              Node n(KLV_KEY_OPERATIONAL_MODE,
                     std::vector<ossim_uint8>(buffer.begin()+idx,
                                              buffer.begin()+idx+length));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              //std::cout << "KLV_KEY_UAS_LDS_VERSION_NUMBER: " << valueAsString(KLV_KEY_UAS_LDS_VERSION_NUMBER) <<std::endl;
              // UAS LDS Version Number
              break;
	   }

           case 78:
           {
              // Map 0..(2^16-1) to -900..19000.
              ossim_uint16 buf = *reinterpret_cast<const ossim_uint16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, 0, 65535, -900, 19000);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_FRAME_CENTER_HEIGHT_ABOVE_ELLIPSOID,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 79:
           {
              // Map -(2^15-1)..(2^15-1) to +/-327.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -327, 327);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_NORTH_VELOCITY,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 80:
           {
              // Map -(2^15-1)..(2^15-1) to +/-327.
              ossim_int16 buf = *reinterpret_cast<const ossim_int16*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -32767, 32767, -327, 327);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_SENSOR_EAST_VELOCITY,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
	   case 82:
	   {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LATITUDE_POINT_1,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
	   }
	   case 83:
	   {
              // Map -(2^31-1)..(2^31-1) to +/-180
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180.0, 180.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LONGITUDE_POINT_1,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
	   }
           case 84:
           {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LATITUDE_POINT_2,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 85:
           {
              // Map -(2^31-1)..(2^31-1) to +/-180
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180.0, 180.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LONGITUDE_POINT_2,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 86:
           {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LATITUDE_POINT_3,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 87:
           {
              // Map -(2^31-1)..(2^31-1) to +/-180
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180.0, 180.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LONGITUDE_POINT_3,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 88:
           {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LATITUDE_POINT_4,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 89:
           {
              // Map -(2^31-1)..(2^31-1) to +/-180
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -180.0, 180.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_CORNER_LONGITUDE_POINT_4,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 90:
           {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_PLATFORM_PITCH_ANGLE_FULL,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           case 91:
           {
              // Map -(2^31-1)..(2^31-1) to +/-90
              ossim_int32 buf = *reinterpret_cast<const ossim_int32*>(&buffer.front()+idx);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(buf);
              }
              ossim_float64 value  = mapValue(buf, -2147483647, 2147483647, -90.0, 90.0);
              if(theNeedToSwapFlag)
              {
                 theEndian.swap(value);
              }
              ossim_uint8* tempBuf = reinterpret_cast<ossim_uint8*>(&value);
              Node n(KLV_KEY_PLATFORM_ROLL_ANGLE_FULL,
                     std::vector<ossim_uint8>(tempBuf,
                                              tempBuf+8));
              tempTable.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(n.theId),
                                                     n));
              break;
           }
           default:
           {
		std::cout << "KEY NOT HANDLED "  <<key  << std::endl;
              if(traceDebug() ) std::cout << "KEY NOT HANDLED "  <<key  << std::endl;  
              break;
           }
        }
      }
      idx +=length;
   }
   /*
   ossimDpt pt1,pt2,pt3,pt4;
   if(getFrameCenterOffsets(pt1,pt2,pt3,pt4))
   {
      ossim_float64 lat,lon,elevation;
      if(getFrameCenter(lat, lon, elevation))
      {
         ossim_float64 cornerLat[4];
         ossim_float64 cornerLon[4];

         cornerLat[0] = lat + pt1.lat;
         cornerLat[1] = lat + pt2.lat;
         cornerLat[2] = lat + pt3.lat;
         cornerLat[3] = lat + pt4.lat;
         cornerLon[0] = lon + pt1.lon;
         cornerLon[1] = lon + pt2.lon;
         cornerLon[2] = lon + pt3.lon;
         cornerLon[3] = lon + pt4.lon;


         if(theNeedToSwapFlag)
         {
            theEndian.swap(cornerLat[0]);
            theEndian.swap(cornerLat[1]);
            theEndian.swap(cornerLat[2]);
            theEndian.swap(cornerLat[3]);
            theEndian.swap(cornerLon[0]);
            theEndian.swap(cornerLon[1]);
            theEndian.swap(cornerLon[2]);
            theEndian.swap(cornerLon[3]);
         }

         ossim_uint8* cornerLat1Buf = reinterpret_cast<ossim_uint8*>(&cornerLat[0]);
         Node cornerLat1Node(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_1,
                std::vector<ossim_uint8>(cornerLat1Buf,
                                         cornerLat1Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLat1Node.theId),
                                                cornerLat1Node));
         ossim_uint8* cornerLat2Buf = reinterpret_cast<ossim_uint8*>(&cornerLat[1]);
         Node cornerLat2Node(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_2,
                std::vector<ossim_uint8>(cornerLat2Buf,
                                         cornerLat2Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLat2Node.theId),
                                                cornerLat2Node));
         ossim_uint8* cornerLat3Buf = reinterpret_cast<ossim_uint8*>(&cornerLat[2]);
         Node cornerLat3Node(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_3,
                std::vector<ossim_uint8>(cornerLat3Buf,
                                         cornerLat3Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLat3Node.theId),
                                                cornerLat3Node));
         ossim_uint8* cornerLat4Buf = reinterpret_cast<ossim_uint8*>(&cornerLat[3]);
         Node cornerLat4Node(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_4,
                std::vector<ossim_uint8>(cornerLat4Buf,
                                         cornerLat4Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLat4Node.theId),
                                                cornerLat4Node));


         ossim_uint8* cornerLon1Buf = reinterpret_cast<ossim_uint8*>(&cornerLon[0]);
         Node cornerLon1Node(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_1,
                std::vector<ossim_uint8>(cornerLon1Buf,
                                         cornerLon1Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLon1Node.theId),
                                                cornerLon1Node));
         ossim_uint8* cornerLon2Buf = reinterpret_cast<ossim_uint8*>(&cornerLon[1]);
         Node cornerLon2Node(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_2,
                std::vector<ossim_uint8>(cornerLon2Buf,
                                         cornerLon2Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLon2Node.theId),
                                                cornerLon2Node));
         ossim_uint8* cornerLon3Buf = reinterpret_cast<ossim_uint8*>(&cornerLon[2]);
         Node cornerLon3Node(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_3,
                std::vector<ossim_uint8>(cornerLon3Buf,
                                         cornerLon3Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLon3Node.theId),
                                                cornerLon3Node));
         ossim_uint8* cornerLon4Buf = reinterpret_cast<ossim_uint8*>(&cornerLon[3]);
         Node cornerLon4Node(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_4,
                std::vector<ossim_uint8>(cornerLon4Buf,
                                         cornerLon4Buf+8));
         theKlvParameters.insert(std::make_pair(static_cast<ossimPredatorKlvIndex>(cornerLon4Node.theId),
                                                cornerLon4Node));
       
  // std::cout << "corner1 = " << valueAsString(KLV_KEY_OFFSET_CORNER_LATITUDE_POINT_1) << ", " 
   //          << valueAsString(KLV_KEY_OFFSET_CORNER_LONGITUDE_POINT_1) << std::endl;
      }
   }
   */
}

std::ostream& ossimPredatorKlvTable::print(std::ostream& out)const
{
  klvMapType::const_iterator iter = theKlvParameters.begin();
  while(iter!=theKlvParameters.end())
  {
    //for (klvMapType::const_iterator iter=theKlvParameters.equal_range(id).first; iter!=theKlvParameters.equal_range(id).second; ++iter)
    //{
    int idx = findPredatorKlvIndexByKey((*iter).second.theId);
    if(idx >= 0)
    {
        //out << (*iter).second.theId << "," << (*iter).first<< ", " << OSSIM_PREDATOR_UDS_TABLE[idx].theName << ": " << valueAsString((*iter).first) << "\n";
      out << OSSIM_PREDATOR_UDS_TABLE[idx].theName <<  " " << ossimString::toString((*iter).second.theSet) << ":" << ossimString::toString((*iter).second.theIndex) << " " << valueAsString((*iter).first, (*iter).second.theSet, (*iter).second.theIndex) << "\n";
    }
    ++iter;
    //}
  }
  return out;
}

ossim_uint16 ossimPredatorKlvTable::compute16BitChecksum(const std::vector<ossim_uint8>& checksumBuffer)const
{

  const ossim_uint8* buf= &checksumBuffer.front();
  ossim_uint16 len = checksumBuffer.size();
 // Initialize Checksum and counter variables.
  ossim_uint16 bcc = 0, i=0;

  // Sum each 16-bit chunk within the buffer into a checksum
  for ( i = 0 ; i < len; ++i)
    bcc += buf[i] << (8 * ((i + 1) % 2));
  return bcc;
}
