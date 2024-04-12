static jboolean android_net_wifi_setPnoListNative(
 JNIEnv *env, jclass cls, jint iface, jint id, jobject list) {

 JNIHelper helper(env);
    wifi_epno_handler handler;
    handler.on_network_found = &onPnoNetworkFound;

    wifi_interface_handle handle = getIfaceHandle(helper, cls, iface);
    ALOGD("configure ePno list request [%d] = %p", id, handle);

 if (list == NULL) {
 int result = hal_fn.wifi_set_epno_list(id, handle, 0, NULL, handler);
        ALOGE(" setPnoListNative: STOP result = %d", result);
 return result >= 0;
 }

    wifi_epno_network net_list[MAX_PNO_SSID];
    memset(&net_list, 0, sizeof(net_list));

 size_t len = helper.getArrayLength((jobjectArray)list);
 if (len > (size_t)MAX_PNO_SSID) {
 return false;
 }

 for (unsigned int i = 0; i < len; i++) {

 JNIObject<jobject> pno_net = helper.getObjectArrayElement((jobjectArray)list, i);
 if (pno_net == NULL) {
            ALOGD("setPnoListNative: could not get element %d", i);
 continue;
 }

 JNIObject<jstring> sssid = helper.getStringField(pno_net, "SSID");
 if (sssid == NULL) {
              ALOGE("Error setPnoListNative: getting ssid field");
 return false;
 }

 ScopedUtfChars chars(env, (jstring)sssid.get());
 const char *ssid = chars.c_str();
 if (ssid == NULL) {
             ALOGE("Error setPnoListNative: getting ssid");
 return false;
 }
 int ssid_len = strnlen((const char*)ssid, 33);
 if (ssid_len > 32) {
           ALOGE("Error setPnoListNative: long ssid %u", strnlen((const char*)ssid, 256));
 return false;
 }

 if (ssid_len > 1 && ssid[0] == '"' && ssid[ssid_len-1])
 {
            ssid++;
            ssid_len-=2;
 }
 if (ssid_len == 0) {
            ALOGE("Error setPnoListNative: zero length ssid, skip it");
 continue;
 }
        memcpy(net_list[i].ssid, ssid, ssid_len);

 int rssit = helper.getIntField(pno_net, "rssi_threshold");
        net_list[i].rssi_threshold = (byte)rssit;
 int a = helper.getIntField(pno_net, "auth");
        net_list[i].auth_bit_field = a;
 int f = helper.getIntField(pno_net, "flags");
        net_list[i].flags = f;
        ALOGE(" setPnoListNative: idx %u rssi %d/%d auth %x/%x flags %x/%x [%s]", i,
 (signed)net_list[i].rssi_threshold, net_list[i].rssi_threshold,
                net_list[i].auth_bit_field, a, net_list[i].flags, f, net_list[i].ssid);
 }

 int result = hal_fn.wifi_set_epno_list(id, handle, len, net_list, handler);
    ALOGE(" setPnoListNative: result %d", result);

 return result >= 0;
}
