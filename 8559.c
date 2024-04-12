static void ssp_request_callback(bt_bdaddr_t *bd_addr, bt_bdname_t *bdname, uint32_t cod,
 bt_ssp_variant_t pairing_variant, uint32_t pass_key) {
    jbyteArray addr, devname;
 if (!checkCallbackThread()) {
       ALOGE("Callback: '%s' is not called on the correct thread", __FUNCTION__);
 return;
 }
 if (!bd_addr) {
        ALOGE("Address is null in %s", __FUNCTION__);
 return;
 }

    addr = callbackEnv->NewByteArray(sizeof(bt_bdaddr_t));
 if (addr == NULL) goto Fail;
    callbackEnv->SetByteArrayRegion(addr, 0, sizeof(bt_bdaddr_t), (jbyte *)bd_addr);

    devname = callbackEnv->NewByteArray(sizeof(bt_bdname_t));
 if (devname == NULL) goto Fail;
    callbackEnv->SetByteArrayRegion(devname, 0, sizeof(bt_bdname_t), (jbyte*)bdname);

    callbackEnv->CallVoidMethod(sJniCallbacksObj, method_sspRequestCallback, addr, devname, cod,
 (jint) pairing_variant, pass_key);

    checkAndClearExceptionFromCallback(callbackEnv, __FUNCTION__);
    callbackEnv->DeleteLocalRef(addr);
    callbackEnv->DeleteLocalRef(devname);
 return;

Fail:
 if (addr) callbackEnv->DeleteLocalRef(addr);
 if (devname) callbackEnv->DeleteLocalRef(devname);

    ALOGE("Error while allocating in: %s", __FUNCTION__);
}
