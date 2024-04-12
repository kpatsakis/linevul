static int getConnectionStateNative(JNIEnv* env, jobject obj, jbyteArray address) {
    ALOGV("%s:",__FUNCTION__);
 if (!sBluetoothInterface) return JNI_FALSE;

    jbyte *addr = env->GetByteArrayElements(address, NULL);
 if (addr == NULL) {
        jniThrowIOException(env, EINVAL);
 return JNI_FALSE;
 }

 int ret = sBluetoothInterface->get_connection_state((bt_bdaddr_t *)addr);
    env->ReleaseByteArrayElements(address, addr, 0);

 return ret;
}
