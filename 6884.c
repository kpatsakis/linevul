static jobject android_net_wifi_get_ring_buffer_status (JNIEnv *env, jclass cls, jint iface) {

 JNIHelper helper(env);
    wifi_interface_handle handle = getIfaceHandle(helper, cls, iface);

    ALOGD("android_net_wifi_get_ring_buffer_status = %p", handle);

 if (handle == 0) {
 return NULL;
 }

    u32 num_rings = 10;
    wifi_ring_buffer_status *status =
 (wifi_ring_buffer_status *)malloc(sizeof(wifi_ring_buffer_status) * num_rings);
 if (!status) return NULL;
    memset(status, 0, sizeof(wifi_ring_buffer_status) * num_rings);
    wifi_error result = hal_fn.wifi_get_ring_buffers_status(handle, &num_rings, status);
 if (result == WIFI_SUCCESS) {
        ALOGD("status is %p, number is %d", status, num_rings);

 JNIObject<jobjectArray> ringBuffersStatus = helper.newObjectArray(
            num_rings, "com/android/server/wifi/WifiNative$RingBufferStatus", NULL);

        wifi_ring_buffer_status *tmp = status;

 for(u32 i = 0; i < num_rings; i++, tmp++) {

 JNIObject<jobject> ringStatus = helper.createObject(
 "com/android/server/wifi/WifiNative$RingBufferStatus");

 if (ringStatus == NULL) {
                ALOGE("Error in creating ringBufferStatus");
                free(status);
 return NULL;
 }

 char name[32];
 for(int j = 0; j < 32; j++) {
                name[j] = tmp->name[j];
 }

            helper.setStringField(ringStatus, "name", name);
            helper.setIntField(ringStatus, "flag", tmp->flags);
            helper.setIntField(ringStatus, "ringBufferId", tmp->ring_id);
            helper.setIntField(ringStatus, "ringBufferByteSize", tmp->ring_buffer_byte_size);
            helper.setIntField(ringStatus, "verboseLevel", tmp->verbose_level);
            helper.setIntField(ringStatus, "writtenBytes", tmp->written_bytes);
            helper.setIntField(ringStatus, "readBytes", tmp->read_bytes);
            helper.setIntField(ringStatus, "writtenRecords", tmp->written_records);

            helper.setObjectArrayElement(ringBuffersStatus, i, ringStatus);
 }

        free(status);
 return ringBuffersStatus.detach();
 } else {
        free(status);
 return NULL;
 }
}
