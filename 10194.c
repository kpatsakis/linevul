void WebPluginImpl::RemoveClient(WebURLLoader* loader) {
  for (size_t i = 0; i < clients_.size(); ++i) {
    if (clients_[i].loader.get() == loader) {
      RemoveClient(i);
      return;
    }
  }
}
