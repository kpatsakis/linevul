status_t MediaRecorder::setPreviewSurface(const sp<IGraphicBufferProducer>& surface)
{
    ALOGV("setPreviewSurface(%p)", surface.get());
 if (mMediaRecorder == NULL) {
        ALOGE("media recorder is not initialized yet");
 return INVALID_OPERATION;
 }
 if (!(mCurrentState & MEDIA_RECORDER_DATASOURCE_CONFIGURED)) {
        ALOGE("setPreviewSurface called in an invalid state(%d)", mCurrentState);
 return INVALID_OPERATION;
 }
 if (!mIsVideoSourceSet) {
        ALOGE("try to set preview surface without setting the video source first");
 return INVALID_OPERATION;
 }

 status_t ret = mMediaRecorder->setPreviewSurface(surface);
 if (OK != ret) {
        ALOGV("setPreviewSurface failed: %d", ret);
        mCurrentState = MEDIA_RECORDER_ERROR;
 return ret;
 }
 return ret;
}
