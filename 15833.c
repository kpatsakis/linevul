void WebFrameLoaderClient::dispatchDidReceiveTitle(const String& title) {
  if (webframe_->client()) {
    webframe_->client()->didReceiveTitle(
        webframe_, webkit_glue::StringToWebString(title));
  }
}
