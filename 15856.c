void DevToolsWindow::OnLoadCompleted() {
  WebContents* inspected_web_contents = GetInspectedWebContents();
  if (inspected_web_contents) {
    SessionTabHelper* session_tab_helper =
        SessionTabHelper::FromWebContents(inspected_web_contents);
    if (session_tab_helper) {
      base::Value tabId(session_tab_helper->session_id().id());
      bindings_->CallClientFunction("DevToolsAPI.setInspectedTabId",
                                    &tabId, NULL, NULL);
    }
  }

  if (life_stage_ == kClosing)
    return;

  if (life_stage_ != kLoadCompleted) {
    life_stage_ = life_stage_ == kIsDockedSet ? kLoadCompleted : kOnLoadFired;
  }
  if (life_stage_ == kLoadCompleted)
    LoadCompleted();
}
