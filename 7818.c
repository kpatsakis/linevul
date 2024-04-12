status_t MediaRecorder::setAudioEncoder(int ae)
{
    ALOGV("setAudioEncoder(%d)", ae);
 if (mMediaRecorder == NULL) {
        ALOGE("media recorder is not initialized yet");
 return INVALID_OPERATION;
 }
 if (!mIsAudioSourceSet) {
        ALOGE("try to set the audio encoder without setting the audio source first");
 return INVALID_OPERATION;
 }
 if (mIsAudioEncoderSet) {
        ALOGE("audio encoder has already been set");
 return INVALID_OPERATION;
 }
 if (!(mCurrentState & MEDIA_RECORDER_DATASOURCE_CONFIGURED)) {
        ALOGE("setAudioEncoder called in an invalid state(%d)", mCurrentState);
 return INVALID_OPERATION;
 }

 status_t ret = mMediaRecorder->setAudioEncoder(ae);
 if (OK != ret) {
        ALOGV("setAudioEncoder failed: %d", ret);
        mCurrentState = MEDIA_RECORDER_ERROR;
 return ret;
 }
    mIsAudioEncoderSet = true;
 return ret;
}
