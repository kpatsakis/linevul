void PrintWebViewHelper::ShowScriptedPrintPreview() {
  if (is_scripted_preview_delayed_) {
    is_scripted_preview_delayed_ = false;
    Send(new PrintHostMsg_ShowScriptedPrintPreview(
        routing_id(), print_preview_context_.IsModifiable()));
  }
}
