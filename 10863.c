sp<IMemory> MetadataRetrieverClient::extractAlbumArt()
{
    ALOGV("extractAlbumArt");
 Mutex::Autolock lock(mLock);
    mAlbumArt.clear();
 if (mRetriever == NULL) {
        ALOGE("retriever is not initialized");
 return NULL;
 }
 MediaAlbumArt *albumArt = mRetriever->extractAlbumArt();
 if (albumArt == NULL) {
        ALOGE("failed to extract an album art");
 return NULL;
 }
 size_t size = sizeof(MediaAlbumArt) + albumArt->size();
    sp<MemoryHeapBase> heap = new MemoryHeapBase(size, 0, "MetadataRetrieverClient");
 if (heap == NULL) {
        ALOGE("failed to create MemoryDealer object");
 delete albumArt;
 return NULL;
 }
    mAlbumArt = new MemoryBase(heap, 0, size);
 if (mAlbumArt == NULL) {
        ALOGE("not enough memory for MediaAlbumArt size=%u", size);
 delete albumArt;
 return NULL;
 }
 MediaAlbumArt::init((MediaAlbumArt *) mAlbumArt->pointer(),
                        albumArt->size(), albumArt->data());
 delete albumArt; // We've taken our copy.
 return mAlbumArt;
}
