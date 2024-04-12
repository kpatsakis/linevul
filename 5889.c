static int connectSocketNative(JNIEnv *env, jobject object, jbyteArray address, jint type,
                                   jbyteArray uuidObj, jint channel, jint flag) {
    jbyte *addr = NULL, *uuid = NULL;
 int socket_fd;
 bt_status_t status;

 if (!sBluetoothSocketInterface) return -1;

    addr = env->GetByteArrayElements(address, NULL);
 if (!addr) {
        ALOGE("failed to get Bluetooth device address");
 goto Fail;
 }

 if(uuidObj != NULL) {
        uuid = env->GetByteArrayElements(uuidObj, NULL);
 if (!uuid) {
            ALOGE("failed to get uuid");
 goto Fail;
 }
 }

 if ( (status = sBluetoothSocketInterface->connect((bt_bdaddr_t *) addr, (btsock_type_t) type,
 (const uint8_t*) uuid, channel, &socket_fd, flag)) != BT_STATUS_SUCCESS) {
        ALOGE("Socket connection failed: %d", status);
 goto Fail;
 }


 if (socket_fd < 0) {
        ALOGE("Fail to create file descriptor on socket fd");
 goto Fail;
 }
    env->ReleaseByteArrayElements(address, addr, 0);
    env->ReleaseByteArrayElements(uuidObj, uuid, 0);
 return socket_fd;

Fail:
 if (addr) env->ReleaseByteArrayElements(address, addr, 0);
 if (uuid) env->ReleaseByteArrayElements(uuidObj, uuid, 0);

 return -1;
}
