status_t Camera2Client::removeFrameListener(int32_t minId, int32_t maxId,
        wp<camera2::FrameProcessor::FilteredListener> listener) {
 return mFrameProcessor->removeListener(minId, maxId, listener);
}
