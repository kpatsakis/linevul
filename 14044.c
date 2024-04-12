void ACodec::onFrameRendered(int64_t mediaTimeUs, nsecs_t systemNano) {
 if (mRenderTracker.onFrameRendered(mediaTimeUs, systemNano) != OK) {
        mRenderTracker.dumpRenderQueue();
 }
}
