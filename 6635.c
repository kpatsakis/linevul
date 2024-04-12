bool WebKitTestController::IsMainWindow(WebContents* web_contents) const {
  return main_window_ && web_contents == main_window_->web_contents();
}
