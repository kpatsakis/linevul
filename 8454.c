static void on_alert_data(wifi_request_id id, char *buffer, int buffer_size, int err_code){

 JNIHelper helper(mVM);
    ALOGD("on_alert_data called, vm = %p, obj = %p, buffer_size = %d, error code = %d"
 , mVM, mCls, buffer_size, err_code);

 if (buffer_size > 0) {
 JNIObject<jbyteArray> records = helper.newByteArray(buffer_size);
        jbyte *bytes = (jbyte *) buffer;
        helper.setByteArrayRegion(records, 0,buffer_size, bytes);
        helper.reportEvent(mCls,"onWifiAlert","([BI)V", records.get(), err_code);
 } else {
        helper.reportEvent(mCls,"onWifiAlert","([BI)V", NULL, err_code);
 }
}
