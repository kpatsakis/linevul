void WebFrameLoaderClient::dispatchDidFinishLoad() {
  OwnPtr<WebPluginLoadObserver> plugin_load_observer = GetPluginLoadObserver();

  if (webframe_->client())
    webframe_->client()->didFinishLoad(webframe_);

  if (plugin_load_observer)
    plugin_load_observer->didFinishLoading();

}
