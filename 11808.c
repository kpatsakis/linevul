uint32_t Visualizer_getDeltaTimeMsFromUpdatedTime(VisualizerContext* pContext) {
 uint32_t deltaMs = 0;
 if (pContext->mBufferUpdateTime.tv_sec != 0) {
 struct timespec ts;
 if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
 time_t secs = ts.tv_sec - pContext->mBufferUpdateTime.tv_sec;
 long nsec = ts.tv_nsec - pContext->mBufferUpdateTime.tv_nsec;
 if (nsec < 0) {
 --secs;
                nsec += 1000000000;
 }
            deltaMs = secs * 1000 + nsec / 1000000;
 }
 }
 return deltaMs;
}
