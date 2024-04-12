void TestingAutomationProvider::ExecuteJavascriptInRenderView(
    DictionaryValue* args,
    IPC::Message* reply_message) {
  string16 frame_xpath, javascript, extension_id, url_text;
  std::string error;
  int render_process_id, render_view_id;
  if (!args->GetString("frame_xpath", &frame_xpath)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'frame_xpath' missing or invalid");
    return;
  }
  if (!args->GetString("javascript", &javascript)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'javascript' missing or invalid");
    return;
  }
  if (!args->GetInteger("view.render_process_id", &render_process_id)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'view.render_process_id' missing or invalid");
    return;
  }
  if (!args->GetInteger("view.render_view_id", &render_view_id)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'view.render_view_id' missing or invalid");
    return;
  }

  RenderViewHost* rvh = RenderViewHost::FromID(render_process_id,
                                               render_view_id);
  if (!rvh) {
    AutomationJSONReply(this, reply_message).SendError(
            "A RenderViewHost object was not found with the given view ID.");
    return;
  }

  new DomOperationMessageSender(this, reply_message, true);
  ExecuteJavascriptInRenderViewFrame(frame_xpath, javascript, reply_message,
                                     rvh);
}
