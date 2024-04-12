content::MediaObserver* ChromeContentBrowserClient::GetMediaObserver() {
  return MediaCaptureDevicesDispatcher::GetInstance();
}
