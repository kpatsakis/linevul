void SkiaOutputSurfaceImplTest::UnblockMainThread() {
  DCHECK(!wait_.IsSignaled());
  wait_.Signal();
}
