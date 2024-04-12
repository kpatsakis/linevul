void NuPlayer::NuPlayerStreamListener::start() {
 for (size_t i = 0; i < kNumBuffers; ++i) {
        mSource->onBufferAvailable(i);
 }
}
