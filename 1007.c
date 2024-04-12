status_t CameraClient::initialize(camera_module_t *module) {
 int callingPid = getCallingPid();
 status_t res;

    LOG1("CameraClient::initialize E (pid %d, id %d)", callingPid, mCameraId);

    res = startCameraOps();
 if (res != OK) {
 return res;
 }

 char camera_device_name[10];
    snprintf(camera_device_name, sizeof(camera_device_name), "%d", mCameraId);

    mHardware = new CameraHardwareInterface(camera_device_name);
    res = mHardware->initialize(&module->common);
 if (res != OK) {
        ALOGE("%s: Camera %d: unable to initialize device: %s (%d)",
                __FUNCTION__, mCameraId, strerror(-res), res);
        mHardware.clear();
 return NO_INIT;
 }

    mHardware->setCallbacks(notifyCallback,
            dataCallback,
            dataCallbackTimestamp,
 (void *)mCameraId);

    enableMsgType(CAMERA_MSG_ERROR | CAMERA_MSG_ZOOM | CAMERA_MSG_FOCUS |
                  CAMERA_MSG_PREVIEW_METADATA | CAMERA_MSG_FOCUS_MOVE);

    LOG1("CameraClient::initialize X (pid %d, id %d)", callingPid, mCameraId);
 return OK;
}
