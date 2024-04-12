bool RenderThreadImpl::Send(IPC::Message* msg) {
  bool pumping_events = false;
  if (msg->is_sync()) {
    if (msg->is_caller_pumping_messages()) {
      pumping_events = true;
    }
  }

  std::unique_ptr<blink::scheduler::RendererScheduler::RendererPauseHandle>
      renderer_paused_handle;

  if (pumping_events) {
    renderer_paused_handle = renderer_scheduler_->PauseRenderer();
    WebView::WillEnterModalLoop();
  }

  bool rv = ChildThreadImpl::Send(msg);

  if (pumping_events)
    WebView::DidExitModalLoop();

  return rv;
}
