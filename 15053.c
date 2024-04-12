status_t MediaPlayer::setVideoSurfaceTexture(
 const sp<IGraphicBufferProducer>& bufferProducer)
{
    ALOGV("setVideoSurfaceTexture");
 Mutex::Autolock _l(mLock);
 if (mPlayer == 0) return NO_INIT;
 return mPlayer->setVideoSurfaceTexture(bufferProducer);
}
