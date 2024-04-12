void WebContentsImpl::ShowCreatedWidget(int process_id,
                                        int widget_route_id,
                                        const gfx::Rect& initial_rect) {
  ShowCreatedWidget(process_id, widget_route_id, false, initial_rect);
}
