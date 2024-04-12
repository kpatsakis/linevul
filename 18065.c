ssize_t Camera3Device::getPointCloudBufferSize() const {
 const int FLOATS_PER_POINT=4;
    camera_metadata_ro_entry maxPointCount = mDeviceInfo.find(ANDROID_DEPTH_MAX_DEPTH_SAMPLES);
 if (maxPointCount.count == 0) {
        ALOGE("%s: Camera %d: Can't find maximum depth point cloud size in static metadata!",
                __FUNCTION__, mId);
 return BAD_VALUE;
 }
 ssize_t maxBytesForPointCloud = sizeof(android_depth_points) +
            maxPointCount.data.i32[0] * sizeof(float) * FLOATS_PER_POINT;
 return maxBytesForPointCloud;
}
