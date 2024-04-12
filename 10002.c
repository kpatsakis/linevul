void RenderFrameImpl::WidgetWillClose() {
  FOR_EACH_OBSERVER(RenderFrameObserver, observers_, WidgetWillClose());
}
