void RenderMessageFilter::OnUpdateIsDelayed(const IPC::Message& msg) {
  render_widget_helper_->DidReceiveBackingStoreMsg(msg);
}
