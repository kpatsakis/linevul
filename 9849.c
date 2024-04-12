void TestingAutomationProvider::HandleInspectElementRequest(
    int handle, int x, int y, IPC::Message* reply_message) {
  WebContents* web_contents = GetWebContentsForHandle(handle, NULL);
  if (web_contents) {
    DCHECK(!reply_message_);
    reply_message_ = reply_message;

    DevToolsWindow::InspectElement(web_contents->GetRenderViewHost(), x, y);
  } else {
    AutomationMsg_InspectElement::WriteReplyParams(reply_message, -1);
    Send(reply_message);
  }
}
