status_t CameraClient::autoFocus() {
    LOG1("autoFocus (pid %d)", getCallingPid());

 Mutex::Autolock lock(mLock);
 status_t result = checkPidAndHardware();
 if (result != NO_ERROR) return result;

 return mHardware->autoFocus();
}
