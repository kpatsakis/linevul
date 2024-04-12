void WebContentsImpl::ShowCreatedWidget(int route_id,
                                        bool is_fullscreen,
                                        const gfx::Rect& initial_pos) {
  if (delegate_)
    delegate_->RenderWidgetShowing();

  RenderWidgetHostViewPort* widget_host_view =
      RenderWidgetHostViewPort::FromRWHV(GetCreatedWidget(route_id));
  if (!widget_host_view)
    return;
  if (is_fullscreen)
    widget_host_view->InitAsFullscreen(GetRenderWidgetHostViewPort());
  else
    widget_host_view->InitAsPopup(GetRenderWidgetHostViewPort(), initial_pos);

  RenderWidgetHostImpl* render_widget_host_impl =
      RenderWidgetHostImpl::From(widget_host_view->GetRenderWidgetHost());
  render_widget_host_impl->Init();
  render_widget_host_impl->set_allow_privileged_mouse_lock(is_fullscreen);

#if defined(OS_MACOSX)
  base::mac::NSObjectRelease(widget_host_view->GetNativeView());
#endif
}
