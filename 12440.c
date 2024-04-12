void AudioSource::releaseQueuedFrames_l() {
    ALOGV("releaseQueuedFrames_l");
 List<MediaBuffer *>::iterator it;
 while (!mBuffersReceived.empty()) {
        it = mBuffersReceived.begin();
 (*it)->release();
        mBuffersReceived.erase(it);
 }
}
