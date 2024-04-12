uint32_t Camera3Device::getDeviceVersion() {
    ATRACE_CALL();
 Mutex::Autolock il(mInterfaceLock);
 return mDeviceVersion;
}
