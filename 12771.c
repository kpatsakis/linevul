void PrintWebViewHelper::DidFinishPrinting(bool success) {
  if (!success) {
    WebView* web_view = print_web_view_;
    if (!web_view)
      web_view = render_view_->webview();

    render_view_->runModalAlertDialog(
        web_view->mainFrame(),
        l10n_util::GetStringUTF16(IDS_PRINT_SPOOL_FAILED_ERROR_TEXT));
  }

  if (print_web_view_) {
    print_web_view_->close();
    print_web_view_ = NULL;
  }
  print_pages_params_.reset();
}
