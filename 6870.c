status_t CameraDeviceClient::getRotationTransformLocked(int32_t* transform) {
    ALOGV("%s: begin", __FUNCTION__);

 if (transform == NULL) {
        ALOGW("%s: null transform", __FUNCTION__);
 return BAD_VALUE;
 }

 *transform = 0;

 const CameraMetadata& staticInfo = mDevice->info();
 camera_metadata_ro_entry_t entry = staticInfo.find(ANDROID_SENSOR_ORIENTATION);
 if (entry.count == 0) {
        ALOGE("%s: Camera %d: Can't find android.sensor.orientation in "
 "static metadata!", __FUNCTION__, mCameraId);
 return INVALID_OPERATION;
 }

 int32_t& flags = *transform;

 int orientation = entry.data.i32[0];
 switch (orientation) {
 case 0:
            flags = 0;
 break;
 case 90:
            flags = NATIVE_WINDOW_TRANSFORM_ROT_90;
 break;
 case 180:
            flags = NATIVE_WINDOW_TRANSFORM_ROT_180;
 break;
 case 270:
            flags = NATIVE_WINDOW_TRANSFORM_ROT_270;
 break;
 default:
            ALOGE("%s: Invalid HAL android.sensor.orientation value: %d",
                  __FUNCTION__, orientation);
 return INVALID_OPERATION;
 }

 /**
     * This magic flag makes surfaceflinger un-rotate the buffers
     * to counter the extra global device UI rotation whenever the user
     * physically rotates the device.
     *
     * By doing this, the camera buffer always ends up aligned
     * with the physical camera for a "see through" effect.
     *
     * In essence, the buffer only gets rotated during preview use-cases.
     * The user is still responsible to re-create streams of the proper
     * aspect ratio, or the preview will end up looking non-uniformly
     * stretched.
     */
    flags |= NATIVE_WINDOW_TRANSFORM_INVERSE_DISPLAY;

    ALOGV("%s: final transform = 0x%x", __FUNCTION__, flags);

 return OK;
}
