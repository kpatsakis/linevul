RenderWidgetFullscreenPepper* RenderFrameImpl::CreatePepperFullscreenContainer(
    PepperPluginInstanceImpl* plugin) {
  GURL active_url;
  if (render_view()->webview())
    active_url = render_view()->GetURLForGraphicsContext3D();

  mojom::WidgetPtr widget_channel;
  mojom::WidgetRequest widget_channel_request =
      mojo::MakeRequest(&widget_channel);

  int32_t fullscreen_widget_routing_id = MSG_ROUTING_NONE;
  if (!RenderThreadImpl::current_render_message_filter()
           ->CreateFullscreenWidget(render_view()->routing_id(),
                                    std::move(widget_channel),
                                    &fullscreen_widget_routing_id)) {
    return nullptr;
  }
  RenderWidget::ShowCallback show_callback =
      base::Bind(&RenderViewImpl::ShowCreatedFullscreenWidget,
                 render_view()->GetWeakPtr());

  RenderWidgetFullscreenPepper* widget = RenderWidgetFullscreenPepper::Create(
      fullscreen_widget_routing_id, show_callback,
      GetRenderWidget()->compositor_deps(), plugin, active_url,
      GetRenderWidget()->screen_info(), std::move(widget_channel_request));
  widget->Show(blink::kWebNavigationPolicyIgnore);
  return widget;
}
