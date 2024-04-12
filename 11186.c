size_t ACodec::countBuffersOwnedByNativeWindow() const {
 size_t n = 0;

 for (size_t i = 0; i < mBuffers[kPortIndexOutput].size(); ++i) {
 const BufferInfo &info = mBuffers[kPortIndexOutput].itemAt(i);

 if (info.mStatus == BufferInfo::OWNED_BY_NATIVE_WINDOW) {
 ++n;
 }
 }

 return n;
}
