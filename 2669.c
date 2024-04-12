static bool initNative(JNIEnv* env, jobject obj) {
    ALOGV("%s:",__FUNCTION__);

    sJniAdapterServiceObj = env->NewGlobalRef(obj);
    sJniCallbacksObj = env->NewGlobalRef(env->GetObjectField(obj, sJniCallbacksField));

 if (sBluetoothInterface) {
 int ret = sBluetoothInterface->init(&sBluetoothCallbacks);
 if (ret != BT_STATUS_SUCCESS) {
            ALOGE("Error while setting the callbacks: %d\n", ret);
            sBluetoothInterface = NULL;
 return JNI_FALSE;
 }
        ret = sBluetoothInterface->set_os_callouts(&sBluetoothOsCallouts);
 if (ret != BT_STATUS_SUCCESS) {
            ALOGE("Error while setting Bluetooth callouts: %d\n", ret);
            sBluetoothInterface->cleanup();
            sBluetoothInterface = NULL;
 return JNI_FALSE;
 }

 if ( (sBluetoothSocketInterface = (btsock_interface_t *)
                  sBluetoothInterface->get_profile_interface(BT_PROFILE_SOCKETS_ID)) == NULL) {
                ALOGE("Error getting socket interface");
 }

 return JNI_TRUE;
 }
 return JNI_FALSE;
}
