gfx::NativeWindow Browser::BrowserShowHtmlDialog(
    HtmlDialogUIDelegate* delegate, gfx::NativeWindow parent_window) {
  return window_->ShowHTMLDialog(delegate, parent_window);
}
