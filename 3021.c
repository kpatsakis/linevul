void CameraClient::setPreviewCallbackFlag(int callback_flag) {
    LOG1("setPreviewCallbackFlag(%d) (pid %d)", callback_flag, getCallingPid());
 Mutex::Autolock lock(mLock);
 if (checkPidAndHardware() != NO_ERROR) return;

    mPreviewCallbackFlag = callback_flag;
 if (mPreviewCallbackFlag & CAMERA_FRAME_CALLBACK_FLAG_ENABLE_MASK) {
        enableMsgType(CAMERA_MSG_PREVIEW_FRAME);
 } else {
        disableMsgType(CAMERA_MSG_PREVIEW_FRAME);
 }
}
