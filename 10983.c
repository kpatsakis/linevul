void SkiaOutputSurfaceImpl::AddContextLostObserver(
    ContextLostObserver* observer) {
  observers_.AddObserver(observer);
}
