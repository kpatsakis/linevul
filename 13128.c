void WebKitTestController::OnTestFinished() {
  test_phase_ = CLEAN_UP;
  if (!printer_->output_finished())
    printer_->PrintImageFooter();
  RenderViewHost* render_view_host =
      main_window_->web_contents()->GetRenderViewHost();
  main_window_->web_contents()->ExitFullscreen();
  base::MessageLoop::current()->PostTask(
      FROM_HERE,
      base::Bind(base::IgnoreResult(&WebKitTestController::Send),
                 base::Unretained(this),
                 new ShellViewMsg_Reset(render_view_host->GetRoutingID())));
}
