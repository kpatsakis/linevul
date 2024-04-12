void PrintWebViewHelper::didStopLoading() {
  PrintPages(print_web_view_->mainFrame(), WebKit::WebNode());
}
