void RenderThreadImpl::UpdateScrollbarTheme(
    mojom::UpdateScrollbarThemeParamsPtr params) {
#if defined(OS_MACOSX)
  static_cast<WebScrollbarBehaviorImpl*>(
      blink_platform_impl_->ScrollbarBehavior())
      ->set_jump_on_track_click(params->jump_on_track_click);

  blink::WebScrollbarTheme::UpdateScrollbarsWithNSDefaults(
      params->initial_button_delay, params->autoscroll_button_delay,
      params->preferred_scroller_style, params->redraw,
      params->button_placement);

  is_elastic_overscroll_enabled_ = params->scroll_view_rubber_banding;
#else
  NOTREACHED();
#endif
}
