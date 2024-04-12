status_t OMXCodec::stop() {
    CODEC_LOGV("stop mState=%d", mState);
 Mutex::Autolock autoLock(mLock);
 status_t err = stopOmxComponent_l();
    mSource->stop();

    CODEC_LOGV("stopped in state %d", mState);
 return err;
}
