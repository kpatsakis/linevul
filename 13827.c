int LocalDOMWindow::screenY() const {
  if (!GetFrame())
    return 0;

  Page* page = GetFrame()->GetPage();
  if (!page)
    return 0;

  ChromeClient& chrome_client = page->GetChromeClient();
  if (page->GetSettings().GetReportScreenSizeInPhysicalPixelsQuirk())
    return lroundf(chrome_client.RootWindowRect().Y() *
                   chrome_client.GetScreenInfo().device_scale_factor);
  return chrome_client.RootWindowRect().Y();
}
