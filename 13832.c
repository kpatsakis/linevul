bool RenderViewImpl::RunJavaScriptMessage(JavaScriptMessageType type,
                                          const string16& message,
                                          const string16& default_value,
                                          const GURL& frame_url,
                                          string16* result) {
  bool success = false;
  string16 result_temp;
  if (!result)
    result = &result_temp;

  SendAndRunNestedMessageLoop(new ViewHostMsg_RunJavaScriptMessage(
      routing_id_, message, default_value, frame_url, type, &success, result));
  return success;
}
