WebKit::WebColorChooser* RenderViewImpl::createColorChooser(
    WebKit::WebColorChooserClient* client,
    const WebKit::WebColor& initial_color) {
  RendererWebColorChooserImpl* color_chooser =
      new RendererWebColorChooserImpl(this, client);
  color_chooser->Open(static_cast<SkColor>(initial_color));
  return color_chooser;
}
