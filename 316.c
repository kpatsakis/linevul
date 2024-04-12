WebUIBindings* RenderView::GetWebUIBindings() {
  if (!web_ui_bindings_.get()) {
    web_ui_bindings_.reset(new WebUIBindings());
  }
  return web_ui_bindings_.get();
}
