CameraMetadata Camera3Device::getLatestRequestLocked() {
    ALOGV("%s", __FUNCTION__);

 CameraMetadata retVal;

 if (mRequestThread != NULL) {
        retVal = mRequestThread->getLatestRequest();
 }

 return retVal;
}
