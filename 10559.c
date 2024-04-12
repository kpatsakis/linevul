void WebLocalFrameImpl::DidFinish() {
  if (!Client())
    return;

  if (WebPluginContainerImpl* plugin = GetFrame()->GetWebPluginContainer())
    plugin->DidFinishLoading();

  Client()->DidFinishLoad();
}
