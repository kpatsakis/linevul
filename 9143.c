NPError WebPluginDelegatePepper::Device2DInitializeContext(
    const NPDeviceContext2DConfig* config,
    NPDeviceContext2D* context) {

  if (!render_view_) {
    return NPERR_GENERIC_ERROR;
  }

  plugin_->SetWindow(NULL);

  scoped_ptr<Graphics2DDeviceContext> g2d(new Graphics2DDeviceContext());
  NPError status = g2d->Initialize(window_rect_, config, context);
  if (NPERR_NO_ERROR == status) {
    context->reserved = reinterpret_cast<void *>(
        graphic2d_contexts_.Add(g2d.release()));
  }
  return status;
}
