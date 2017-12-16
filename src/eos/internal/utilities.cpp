#include "utilities.hpp"

#include <edsdk/EDSDKErrors.h>

namespace EOS {
  namespace Internal {
    static EdsError lastError{EDS_ERR_OK};

    std::string errorToString(EdsError error) {
      switch (error) {
        /*-----------------------------------------------------------------------
        ED-SDK Error Code Masks
        ------------------------------------------------------------------------*/
      case EDS_ISSPECIFIC_MASK:
        return "EDS_ISSPECIFIC_MASK";
      case EDS_COMPONENTID_MASK:
        return "EDS_COMPONENTID_MASK";
      case EDS_RESERVED_MASK:
        return "EDS_RESERVED_MASK";
      case EDS_ERRORID_MASK:
        return "EDS_ERRORID_MASK";

        /*-----------------------------------------------------------------------
        ED-SDK Base Component IDs
        ------------------------------------------------------------------------*/
      case EDS_CMP_ID_CLIENT_COMPONENTID:
        return "EDS_CMP_ID_CLIENT_COMPONENTID";
      case EDS_CMP_ID_LLSDK_COMPONENTID:
        return "EDS_CMP_ID_LLSDK_COMPONENTID";
      case EDS_CMP_ID_HLSDK_COMPONENTID:
        return "EDS_CMP_ID_HLSDK_COMPONENTID";

        /*-----------------------------------------------------------------------
        ED-SDK Functin Success Code
        ------------------------------------------------------------------------*/
      case EDS_ERR_OK:
        return "EDS_ERR_OK";

        /*-----------------------------------------------------------------------
        ED-SDK Generic Error IDs
        ------------------------------------------------------------------------*/
        /* Miscellaneous errors */
      case EDS_ERR_UNIMPLEMENTED:
        return "EDS_ERR_UNIMPLEMENTED";
      case EDS_ERR_INTERNAL_ERROR:
        return "EDS_ERR_INTERNAL_ERROR";
      case EDS_ERR_MEM_ALLOC_FAILED:
        return "EDS_ERR_MEM_ALLOC_FAILED";
      case EDS_ERR_MEM_FREE_FAILED:
        return "EDS_ERR_MEM_FREE_FAILED";
      case EDS_ERR_OPERATION_CANCELLED:
        return "EDS_ERR_OPERATION_CANCELLED";
      case EDS_ERR_INCOMPATIBLE_VERSION:
        return "EDS_ERR_INCOMPATIBLE_VERSION";
      case EDS_ERR_NOT_SUPPORTED:
        return "EDS_ERR_NOT_SUPPORTED";
      case EDS_ERR_UNEXPECTED_EXCEPTION:
        return "EDS_ERR_UNEXPECTED_EXCEPTION";
      case EDS_ERR_PROTECTION_VIOLATION:
        return "EDS_ERR_PROTECTION_VIOLATION";
      case EDS_ERR_MISSING_SUBCOMPONENT:
        return "EDS_ERR_MISSING_SUBCOMPONENT";
      case EDS_ERR_SELECTION_UNAVAILABLE:
        return "EDS_ERR_SELECTION_UNAVAILABLE";

        /* File errors */
      case EDS_ERR_FILE_IO_ERROR:
        return "EDS_ERR_FILE_IO_ERROR";
      case EDS_ERR_FILE_TOO_MANY_OPEN:
        return "EDS_ERR_FILE_TOO_MANY_OPEN";
      case EDS_ERR_FILE_NOT_FOUND:
        return "EDS_ERR_FILE_NOT_FOUND";
      case EDS_ERR_FILE_OPEN_ERROR:
        return "EDS_ERR_FILE_OPEN_ERROR";
      case EDS_ERR_FILE_CLOSE_ERROR:
        return "EDS_ERR_FILE_CLOSE_ERROR";
      case EDS_ERR_FILE_SEEK_ERROR:
        return "EDS_ERR_FILE_SEEK_ERROR";
      case EDS_ERR_FILE_TELL_ERROR:
        return "EDS_ERR_FILE_TELL_ERROR";
      case EDS_ERR_FILE_READ_ERROR:
        return "EDS_ERR_FILE_READ_ERROR";
      case EDS_ERR_FILE_WRITE_ERROR:
        return "EDS_ERR_FILE_WRITE_ERROR";
      case EDS_ERR_FILE_PERMISSION_ERROR:
        return "EDS_ERR_FILE_PERMISSION_ERROR";
      case EDS_ERR_FILE_DISK_FULL_ERROR:
        return "EDS_ERR_FILE_DISK_FULL_ERROR";
      case EDS_ERR_FILE_ALREADY_EXISTS:
        return "EDS_ERR_FILE_ALREADY_EXISTS";
      case EDS_ERR_FILE_FORMAT_UNRECOGNIZED:
        return "EDS_ERR_FILE_FORMAT_UNRECOGNIZED";
      case EDS_ERR_FILE_DATA_CORRUPT:
        return "EDS_ERR_FILE_DATA_CORRUPT";
      case EDS_ERR_FILE_NAMING_NA:
        return "EDS_ERR_FILE_NAMING_NA";

        /* Directory errors */
      case EDS_ERR_DIR_NOT_FOUND:
        return "EDS_ERR_DIR_NOT_FOUND";
      case EDS_ERR_DIR_IO_ERROR:
        return "EDS_ERR_DIR_IO_ERROR";
      case EDS_ERR_DIR_ENTRY_NOT_FOUND:
        return "EDS_ERR_DIR_ENTRY_NOT_FOUND";
      case EDS_ERR_DIR_ENTRY_EXISTS:
        return "EDS_ERR_DIR_ENTRY_EXISTS";
      case EDS_ERR_DIR_NOT_EMPTY:
        return "EDS_ERR_DIR_NOT_EMPTY";

        /* Property errors */
      case EDS_ERR_PROPERTIES_UNAVAILABLE:
        return "EDS_ERR_PROPERTIES_UNAVAILABLE";
      case EDS_ERR_PROPERTIES_MISMATCH:
        return "EDS_ERR_PROPERTIES_MISMATCH";
      case EDS_ERR_PROPERTIES_NOT_LOADED:
        return "EDS_ERR_PROPERTIES_NOT_LOADED";

        /* Function Parameter errors */
      case EDS_ERR_INVALID_PARAMETER:
        return "EDS_ERR_INVALID_PARAMETER";
      case EDS_ERR_INVALID_HANDLE:
        return "EDS_ERR_INVALID_HANDLE";
      case EDS_ERR_INVALID_POINTER:
        return "EDS_ERR_INVALID_POINTER";
      case EDS_ERR_INVALID_INDEX:
        return "EDS_ERR_INVALID_INDEX";
      case EDS_ERR_INVALID_LENGTH:
        return "EDS_ERR_INVALID_LENGTH";
      case EDS_ERR_INVALID_FN_POINTER:
        return "EDS_ERR_INVALID_FN_POINTER";
      case EDS_ERR_INVALID_SORT_FN:
        return "EDS_ERR_INVALID_SORT_FN";

        /* Device errors */
      case EDS_ERR_DEVICE_NOT_FOUND:
        return "EDS_ERR_DEVICE_NOT_FOUND";
      case EDS_ERR_DEVICE_BUSY:
        return "EDS_ERR_DEVICE_BUSY";
      case EDS_ERR_DEVICE_INVALID:
        return "EDS_ERR_DEVICE_INVALID";
      case EDS_ERR_DEVICE_EMERGENCY:
        return "EDS_ERR_DEVICE_EMERGENCY";
      case EDS_ERR_DEVICE_MEMORY_FULL:
        return "EDS_ERR_DEVICE_MEMORY_FULL";
      case EDS_ERR_DEVICE_INTERNAL_ERROR:
        return "EDS_ERR_DEVICE_INTERNAL_ERROR";
      case EDS_ERR_DEVICE_INVALID_PARAMETER:
        return "EDS_ERR_DEVICE_INVALID_PARAMETER";
      case EDS_ERR_DEVICE_NO_DISK:
        return "EDS_ERR_DEVICE_NO_DISK";
      case EDS_ERR_DEVICE_DISK_ERROR:
        return "EDS_ERR_DEVICE_DISK_ERROR";
      case EDS_ERR_DEVICE_CF_GATE_CHANGED:
        return "EDS_ERR_DEVICE_CF_GATE_CHANGED";
      case EDS_ERR_DEVICE_DIAL_CHANGED:
        return "EDS_ERR_DEVICE_DIAL_CHANGED";
      case EDS_ERR_DEVICE_NOT_INSTALLED:
        return "EDS_ERR_DEVICE_NOT_INSTALLED";
      case EDS_ERR_DEVICE_STAY_AWAKE:
        return "EDS_ERR_DEVICE_STAY_AWAKE";
      case EDS_ERR_DEVICE_NOT_RELEASED:
        return "EDS_ERR_DEVICE_NOT_RELEASED";

        /* Stream errors */
      case EDS_ERR_STREAM_IO_ERROR:
        return "EDS_ERR_STREAM_IO_ERROR";
      case EDS_ERR_STREAM_NOT_OPEN:
        return "EDS_ERR_STREAM_NOT_OPEN";
      case EDS_ERR_STREAM_ALREADY_OPEN:
        return "EDS_ERR_STREAM_ALREADY_OPEN";
      case EDS_ERR_STREAM_OPEN_ERROR:
        return "EDS_ERR_STREAM_OPEN_ERROR";
      case EDS_ERR_STREAM_CLOSE_ERROR:
        return "EDS_ERR_STREAM_CLOSE_ERROR";
      case EDS_ERR_STREAM_SEEK_ERROR:
        return "EDS_ERR_STREAM_SEEK_ERROR";
      case EDS_ERR_STREAM_TELL_ERROR:
        return "EDS_ERR_STREAM_TELL_ERROR";
      case EDS_ERR_STREAM_READ_ERROR:
        return "EDS_ERR_STREAM_READ_ERROR";
      case EDS_ERR_STREAM_WRITE_ERROR:
        return "EDS_ERR_STREAM_WRITE_ERROR";
      case EDS_ERR_STREAM_PERMISSION_ERROR:
        return "EDS_ERR_STREAM_PERMISSION_ERROR";
      case EDS_ERR_STREAM_COULDNT_BEGIN_THREAD:
        return "EDS_ERR_STREAM_COULDNT_BEGIN_THREAD";
      case EDS_ERR_STREAM_BAD_OPTIONS:
        return "EDS_ERR_STREAM_BAD_OPTIONS";
      case EDS_ERR_STREAM_END_OF_STREAM:
        return "EDS_ERR_STREAM_END_OF_STREAM";

        /* Communications errors */
      case EDS_ERR_COMM_PORT_IS_IN_USE:
        return "EDS_ERR_COMM_PORT_IS_IN_USE";
      case EDS_ERR_COMM_DISCONNECTED:
        return "EDS_ERR_COMM_DISCONNECTED";
      case EDS_ERR_COMM_DEVICE_INCOMPATIBLE:
        return "EDS_ERR_COMM_DEVICE_INCOMPATIBLE";
      case EDS_ERR_COMM_BUFFER_FULL:
        return "EDS_ERR_COMM_BUFFER_FULL";
      case EDS_ERR_COMM_USB_BUS_ERR:
        return "EDS_ERR_COMM_USB_BUS_ERR";

        /* Lock/Unlock */
      case EDS_ERR_USB_DEVICE_LOCK_ERROR:
        return "EDS_ERR_USB_DEVICE_LOCK_ERROR";
      case EDS_ERR_USB_DEVICE_UNLOCK_ERROR:
        return "EDS_ERR_USB_DEVICE_UNLOCK_ERROR";

        /* STI/WIA */
      case EDS_ERR_STI_UNKNOWN_ERROR:
        return "EDS_ERR_STI_UNKNOWN_ERROR";
      case EDS_ERR_STI_INTERNAL_ERROR:
        return "EDS_ERR_STI_INTERNAL_ERROR";
      case EDS_ERR_STI_DEVICE_CREATE_ERROR:
        return "EDS_ERR_STI_DEVICE_CREATE_ERROR";
      case EDS_ERR_STI_DEVICE_RELEASE_ERROR:
        return "EDS_ERR_STI_DEVICE_RELEASE_ERROR";
      case EDS_ERR_DEVICE_NOT_LAUNCHED:
        return "EDS_ERR_DEVICE_NOT_LAUNCHED";

      case EDS_ERR_ENUM_NA:
        return "EDS_ERR_ENUM_NA";
      case EDS_ERR_INVALID_FN_CALL:
        return "EDS_ERR_INVALID_FN_CALL";
      case EDS_ERR_HANDLE_NOT_FOUND:
        return "EDS_ERR_HANDLE_NOT_FOUND";
      case EDS_ERR_INVALID_ID:
        return "EDS_ERR_INVALID_ID";
      case EDS_ERR_WAIT_TIMEOUT_ERROR:
        return "EDS_ERR_WAIT_TIMEOUT_ERROR";

        /* PTP */
      case EDS_ERR_SESSION_NOT_OPEN:
        return "EDS_ERR_SESSION_NOT_OPEN";
      case EDS_ERR_INVALID_TRANSACTIONID:
        return "EDS_ERR_INVALID_TRANSACTIONID";
      case EDS_ERR_INCOMPLETE_TRANSFER:
        return "EDS_ERR_INCOMPLETE_TRANSFER";
      case EDS_ERR_INVALID_STRAGEID:
        return "EDS_ERR_INVALID_STRAGEID";
      case EDS_ERR_DEVICEPROP_NOT_SUPPORTED:
        return "EDS_ERR_DEVICEPROP_NOT_SUPPORTED";
      case EDS_ERR_INVALID_OBJECTFORMATCODE:
        return "EDS_ERR_INVALID_OBJECTFORMATCODE";
      case EDS_ERR_SELF_TEST_FAILED:
        return "EDS_ERR_SELF_TEST_FAILED";
      case EDS_ERR_PARTIAL_DELETION:
        return "EDS_ERR_PARTIAL_DELETION";
      case EDS_ERR_SPECIFICATION_BY_FORMAT_UNSUPPORTED:
        return "EDS_ERR_SPECIFICATION_BY_FORMAT_UNSUPPORTED";
      case EDS_ERR_NO_VALID_OBJECTINFO:
        return "EDS_ERR_NO_VALID_OBJECTINFO";
      case EDS_ERR_INVALID_CODE_FORMAT:
        return "EDS_ERR_INVALID_CODE_FORMAT";
      case EDS_ERR_UNKNOWN_VENDOR_CODE:
        return "EDS_ERR_UNKNOWN_VENDOR_CODE";
      case EDS_ERR_CAPTURE_ALREADY_TERMINATED:
        return "EDS_ERR_CAPTURE_ALREADY_TERMINATED";
      case EDS_ERR_PTP_DEVICE_BUSY:
        return "EDS_ERR_PTP_DEVICE_BUSY";
      case EDS_ERR_INVALID_PARENTOBJECT:
        return "EDS_ERR_INVALID_PARENTOBJECT";
      case EDS_ERR_INVALID_DEVICEPROP_FORMAT:
        return "EDS_ERR_INVALID_DEVICEPROP_FORMAT";
      case EDS_ERR_INVALID_DEVICEPROP_VALUE:
        return "EDS_ERR_INVALID_DEVICEPROP_VALUE";
      case EDS_ERR_SESSION_ALREADY_OPEN:
        return "EDS_ERR_SESSION_ALREADY_OPEN";
      case EDS_ERR_TRANSACTION_CANCELLED:
        return "EDS_ERR_TRANSACTION_CANCELLED";
      case EDS_ERR_SPECIFICATION_OF_DESTINATION_UNSUPPORTED:
        return "EDS_ERR_SPECIFICATION_OF_DESTINATION_UNSUPPORTED";
      case EDS_ERR_NOT_CAMERA_SUPPORT_SDK_VERSION:
        return "EDS_ERR_NOT_CAMERA_SUPPORT_SDK_VERSION";

        /* PTP Vendor */
      case EDS_ERR_UNKNOWN_COMMAND:
        return "EDS_ERR_UNKNOWN_COMMAND";
      case EDS_ERR_OPERATION_REFUSED:
        return "EDS_ERR_OPERATION_REFUSED";
      case EDS_ERR_LENS_COVER_CLOSE:
        return "EDS_ERR_LENS_COVER_CLOSE";
      case EDS_ERR_LOW_BATTERY:
        return "EDS_ERR_LOW_BATTERY";
      case EDS_ERR_OBJECT_NOTREADY:
        return "EDS_ERR_OBJECT_NOTREADY";
      case EDS_ERR_CANNOT_MAKE_OBJECT:
        return "EDS_ERR_CANNOT_MAKE_OBJECT";
      case EDS_ERR_MEMORYSTATUS_NOTREADY:
        return "EDS_ERR_MEMORYSTATUS_NOTREADY";

        /* Take Picture errors */
      case EDS_ERR_TAKE_PICTURE_AF_NG:
        return "EDS_ERR_TAKE_PICTURE_AF_NG";
      case EDS_ERR_TAKE_PICTURE_RESERVED:
        return "EDS_ERR_TAKE_PICTURE_RESERVED";
      case EDS_ERR_TAKE_PICTURE_MIRROR_UP_NG:
        return "EDS_ERR_TAKE_PICTURE_MIRROR_UP_NG";
      case EDS_ERR_TAKE_PICTURE_SENSOR_CLEANING_NG:
        return "EDS_ERR_TAKE_PICTURE_SENSOR_CLEANING_NG";
      case EDS_ERR_TAKE_PICTURE_SILENCE_NG:
        return "EDS_ERR_TAKE_PICTURE_SILENCE_NG";
      case EDS_ERR_TAKE_PICTURE_NO_CARD_NG:
        return "EDS_ERR_TAKE_PICTURE_NO_CARD_NG";
      case EDS_ERR_TAKE_PICTURE_CARD_NG:
        return "EDS_ERR_TAKE_PICTURE_CARD_NG";
      case EDS_ERR_TAKE_PICTURE_CARD_PROTECT_NG:
        return "EDS_ERR_TAKE_PICTURE_CARD_PROTECT_NG";
      case EDS_ERR_TAKE_PICTURE_MOVIE_CROP_NG:
        return "EDS_ERR_TAKE_PICTURE_MOVIE_CROP_NG";
      case EDS_ERR_TAKE_PICTURE_STROBO_CHARGE_NG:
        return "EDS_ERR_TAKE_PICTURE_STROBO_CHARGE_NG";
      case EDS_ERR_TAKE_PICTURE_NO_LENS_NG:
        return "EDS_ERR_TAKE_PICTURE_NO_LENS_NG";
      case EDS_ERR_TAKE_PICTURE_SPECIAL_MOVIE_MODE_NG:
        return "EDS_ERR_TAKE_PICTURE_SPECIAL_MOVIE_MODE_NG";
      case EDS_ERR_TAKE_PICTURE_LV_REL_PROHIBIT_MODE_NG:
        return "EDS_ERR_TAKE_PICTURE_LV_REL_PROHIBIT_MODE_NG";

      default:
        return "UNKNOWN";
      }
    }

    EdsError getLastError() {
      EdsError error = lastError;
      lastError = EDS_ERR_OK;
      return error;
    }

    bool verifyCall(EdsError error) {
      if (error == EDS_ERR_OK) {
        return true;
      } else {
        lastError = error;
        return false;
      }
    }

    bool verifyRefCountCall(EdsUInt32 result) {
      return result != 0xFFFFFFFF;
    }
  }
}
