void RenderView::OnScriptEvalRequest(const string16& frame_xpath,
                                     const string16& jscript,
                                     int id,
                                     bool notify_result) {
  EvaluateScript(frame_xpath, jscript, id, notify_result);
}
