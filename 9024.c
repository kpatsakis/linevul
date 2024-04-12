void WebContentsImpl::ShowCreatedWidget(int process_id,
                                        int route_id,
                                        const gfx::Rect& initial_rect) {
  ShowCreatedWidget(process_id, route_id, false, initial_rect);
}
