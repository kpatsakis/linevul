bool PrintWebViewHelper::InitPrintSettingsAndPrepareFrame(
    WebKit::WebFrame* frame, const WebKit::WebNode& node,
    scoped_ptr<PrepareFrameAndViewForPrint>* prepare) {
  DCHECK(frame);
  if (!InitPrintSettings()) {
    notify_browser_of_print_failure_ = false;
    render_view()->RunModalAlertDialog(
        frame,
        l10n_util::GetStringUTF16(IDS_PRINT_PREVIEW_INVALID_PRINTER_SETTINGS));
    return false;
  }

  DCHECK(!prepare->get());
  prepare->reset(new PrepareFrameAndViewForPrint(print_pages_params_->params,
                                                 frame, node));
  UpdateFrameAndViewFromCssPageLayout(frame, node, prepare->get(),
                                      print_pages_params_->params,
                                      ignore_css_margins_);
  Send(new PrintHostMsg_DidGetDocumentCookie(
        routing_id(), print_pages_params_->params.document_cookie));
  return true;
}
