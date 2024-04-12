void MediaRecorder::notify(int msg, int ext1, int ext2)
{
    ALOGV("message received msg=%d, ext1=%d, ext2=%d", msg, ext1, ext2);

    sp<MediaRecorderListener> listener;
    mLock.lock();
    listener = mListener;
    mLock.unlock();

 if (listener != NULL) {
 Mutex::Autolock _l(mNotifyLock);
        ALOGV("callback application");
        listener->notify(msg, ext1, ext2);
        ALOGV("back from callback");
 }
}
