BrowserPluginManager* RenderViewImpl::browser_plugin_manager() {
  if (!browser_plugin_manager_)
    browser_plugin_manager_ = BrowserPluginManager::Create(this);
  return browser_plugin_manager_;
}
