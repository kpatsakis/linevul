void Camera3Device::notifyError(const camera3_error_msg_t &msg,
 NotificationListener *listener) {

 static const ICameraDeviceCallbacks::CameraErrorCode
            halErrorMap[CAMERA3_MSG_NUM_ERRORS] = {
 ICameraDeviceCallbacks::ERROR_CAMERA_INVALID_ERROR,
 ICameraDeviceCallbacks::ERROR_CAMERA_DEVICE,
 ICameraDeviceCallbacks::ERROR_CAMERA_REQUEST,
 ICameraDeviceCallbacks::ERROR_CAMERA_RESULT,
 ICameraDeviceCallbacks::ERROR_CAMERA_BUFFER
 };

 ICameraDeviceCallbacks::CameraErrorCode errorCode =
 ((msg.error_code >= 0) &&
 (msg.error_code < CAMERA3_MSG_NUM_ERRORS)) ?
            halErrorMap[msg.error_code] :
 ICameraDeviceCallbacks::ERROR_CAMERA_INVALID_ERROR;

 int streamId = 0;
 if (msg.error_stream != NULL) {
 Camera3Stream *stream =
 Camera3Stream::cast(msg.error_stream);
        streamId = stream->getId();
 }
    ALOGV("Camera %d: %s: HAL error, frame %d, stream %d: %d",
            mId, __FUNCTION__, msg.frame_number,
            streamId, msg.error_code);

 CaptureResultExtras resultExtras;
 switch (errorCode) {
 case ICameraDeviceCallbacks::ERROR_CAMERA_DEVICE:
            SET_ERR("Camera HAL reported serious device error");
 break;
 case ICameraDeviceCallbacks::ERROR_CAMERA_REQUEST:
 case ICameraDeviceCallbacks::ERROR_CAMERA_RESULT:
 case ICameraDeviceCallbacks::ERROR_CAMERA_BUFFER:
 {
 Mutex::Autolock l(mInFlightLock);
 ssize_t idx = mInFlightMap.indexOfKey(msg.frame_number);
 if (idx >= 0) {
 InFlightRequest &r = mInFlightMap.editValueAt(idx);
                    r.requestStatus = msg.error_code;
                    resultExtras = r.resultExtras;
 } else {
                    resultExtras.frameNumber = msg.frame_number;
                    ALOGE("Camera %d: %s: cannot find in-flight request on "
 "frame %" PRId64 " error", mId, __FUNCTION__,
                            resultExtras.frameNumber);
 }
 }
 if (listener != NULL) {
                listener->notifyError(errorCode, resultExtras);
 } else {
                ALOGE("Camera %d: %s: no listener available", mId, __FUNCTION__);
 }
 break;
 default:
            SET_ERR("Unknown error message from HAL: %d", msg.error_code);
 break;
 }
}
