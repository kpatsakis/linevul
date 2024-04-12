void RenderViewTest::SendContentStateImmediately() {
  RenderViewImpl* impl = static_cast<RenderViewImpl*>(view_);
  impl->set_send_content_state_immediately(true);
}
