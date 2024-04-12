SoftAVC::~SoftAVC() {
    H264SwDecRelease(mHandle);
    mHandle = NULL;

 while (mPicToHeaderMap.size() != 0) {
        OMX_BUFFERHEADERTYPE *header = mPicToHeaderMap.editValueAt(0);
        mPicToHeaderMap.removeItemsAt(0);
 delete header;
        header = NULL;
 }
 List<BufferInfo *> &outQueue = getPortQueue(kOutputPortIndex);
 List<BufferInfo *> &inQueue = getPortQueue(kInputPortIndex);
    CHECK(outQueue.empty());
    CHECK(inQueue.empty());

 delete[] mFirstPicture;
}
