void RenderViewHostImpl::OnShowWidget(int route_id,
                                      const gfx::Rect& initial_pos) {
  if (!is_swapped_out_)
    delegate_->ShowCreatedWidget(route_id, initial_pos);
  Send(new ViewMsg_Move_ACK(route_id));
}
