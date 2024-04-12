void WebKitTestController::OnResetDone() {
  if (is_leak_detection_enabled_) {
    if (main_window_ && main_window_->web_contents()) {
      RenderViewHost* render_view_host =
          main_window_->web_contents()->GetRenderViewHost();
      render_view_host->Send(
          new ShellViewMsg_TryLeakDetection(render_view_host->GetRoutingID()));
    }
    return;
  }

  base::MessageLoop::current()->PostTask(FROM_HERE,
                                         base::MessageLoop::QuitClosure());
}
