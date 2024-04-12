void CameraClient::handleGenericData(int32_t msgType,
 const sp<IMemory>& dataPtr, camera_frame_metadata_t *metadata) {
    sp<ICameraClient> c = mRemoteCallback;
    mLock.unlock();
 if (c != 0) {
        c->dataCallback(msgType, dataPtr, metadata);
 }
}
