void BrowserView::ConfirmBrowserCloseWithPendingDownloads() {
  DownloadInProgressDialogView::Show(browser_.get(), GetNativeWindow());
}
