status_t AudioFlinger::EffectModule::remove_effect_from_hal_l()
{
 if ((mDescriptor.flags & EFFECT_FLAG_TYPE_MASK) == EFFECT_FLAG_TYPE_PRE_PROC ||
 (mDescriptor.flags & EFFECT_FLAG_TYPE_MASK) == EFFECT_FLAG_TYPE_POST_PROC) {
        sp<ThreadBase> thread = mThread.promote();
 if (thread != 0) {
 audio_stream_t *stream = thread->stream();
 if (stream != NULL) {
                stream->remove_audio_effect(stream, mEffectInterface);
 }
 }
 }
 return NO_ERROR;
}
