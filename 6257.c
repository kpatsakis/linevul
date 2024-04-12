RenderWidgetFullscreenPepper* RenderFrameImpl::CreatePepperFullscreenContainer(
    PepperPluginInstanceImpl* plugin) {
  blink::WebURL main_frame_url;
  WebFrame* main_frame = render_view()->webview()->MainFrame();
  if (main_frame->IsWebLocalFrame())
    main_frame_url = main_frame->ToWebLocalFrame()->GetDocument().Url();

  mojom::WidgetPtr widget_channel;
  mojom::WidgetRequest widget_channel_request =
      mojo::MakeRequest(&widget_channel);

  int32_t fullscreen_widget_routing_id = MSG_ROUTING_NONE;
  if (!RenderThreadImpl::current_render_message_filter()
           ->CreateFullscreenWidget(render_view()->GetRoutingID(),
                                    std::move(widget_channel),
                                    &fullscreen_widget_routing_id)) {
    return nullptr;
  }
  RenderWidget::ShowCallback show_callback =
      base::BindOnce(&RenderViewImpl::ShowCreatedFullscreenWidget,
                     render_view()->GetWeakPtr());

  RenderWidgetFullscreenPepper* widget = RenderWidgetFullscreenPepper::Create(
      fullscreen_widget_routing_id, std::move(show_callback),
      GetRenderWidget()->compositor_deps(), plugin, std::move(main_frame_url),
      GetRenderWidget()->GetWebScreenInfo(), std::move(widget_channel_request));
  widget->Show(blink::kWebNavigationPolicyCurrentTab);
  return widget;
}
