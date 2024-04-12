void RenderViewHostImpl::RemoveObserver(RenderViewHostObserver* observer) {
  observers_.RemoveObserver(observer);
}
