 bool WebViewPlugin::initialize(WebPluginContainer* container) {
   container_ = container;
   if (container_)
    old_title_ = container_->element().getAttribute("title");
  return true;
}
