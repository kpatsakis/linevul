BrowserWindow* BrowserWindow::CreateBrowserWindow(Browser* browser) {
  BrowserView* view = new BrowserView(browser);
  (new BrowserFrame(view))->InitBrowserFrame();
  view->GetWidget()->non_client_view()->SetAccessibleName(
      l10n_util::GetStringUTF16(IDS_PRODUCT_NAME));
  return view;
}
