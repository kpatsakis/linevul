static void onScanEvent(wifi_scan_event event, unsigned status) {

 JNIHelper helper(mVM);


    helper.reportEvent(mCls, "onScanStatus", "(I)V", event);
}
