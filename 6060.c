void WebFrameLoaderClient::frameLoaderDestroyed() {
  webframe_->Closing();
  webframe_->Release();
}
