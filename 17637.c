void BrowserView::DestroyBrowser() {
  GetWidget()->RemoveObserver(this);
  frame_->CloseNow();
}
