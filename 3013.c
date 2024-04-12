bool RenderView::runModalConfirmDialog(
    WebFrame* frame, const WebString& message) {
  return RunJavaScriptMessage(ui::MessageBoxFlags::kIsJavascriptConfirm,
                              message,
                              string16(),
                              frame->document().url(),
                              NULL);
}
