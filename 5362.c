static int32_t DpbAllocWrapper(void *userData,
 unsigned int sizeInMbs, unsigned int numBuffers) {
 SoftAVCEncoder *encoder = static_cast<SoftAVCEncoder *>(userData);
    CHECK(encoder != NULL);
 return encoder->allocOutputBuffers(sizeInMbs, numBuffers);
}
