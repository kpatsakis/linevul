status_t MediaRecorder::setVideoSource(int vs)
{
    ALOGV("setVideoSource(%d)", vs);
 if (mMediaRecorder == NULL) {
        ALOGE("media recorder is not initialized yet");
 return INVALID_OPERATION;
 }
 if (mIsVideoSourceSet) {
        ALOGE("video source has already been set");
 return INVALID_OPERATION;
 }
 if (mCurrentState & MEDIA_RECORDER_IDLE) {
        ALOGV("Call init() since the media recorder is not initialized yet");
 status_t ret = init();
 if (OK != ret) {
 return ret;
 }
 }
 if (!(mCurrentState & MEDIA_RECORDER_INITIALIZED)) {
        ALOGE("setVideoSource called in an invalid state(%d)", mCurrentState);
 return INVALID_OPERATION;
 }

 status_t ret = mMediaRecorder->setVideoSource(vs);

 if (OK != ret) {
        ALOGV("setVideoSource failed: %d", ret);
        mCurrentState = MEDIA_RECORDER_ERROR;
 return ret;
 }
    mIsVideoSourceSet = true;
 return ret;
}
