void Browser::Search() {
  const GURL& url = GetSelectedTabContents()->GetURL();
  if (url.SchemeIs(chrome::kChromeUIScheme) &&
      url.host() == chrome::kChromeUINewTabHost) {
    CloseTab();
    return;
  }

  if (window_->IsFullscreen()) {
    ToggleFullscreenMode();
    MessageLoop::current()->PostTask(
        FROM_HERE, method_factory_.NewRunnableMethod(&Browser::Search));
    return;
  }

  NewTab();
}
