void RenderViewHostImpl::OnShowView(int route_id,
                                    WindowOpenDisposition disposition,
                                    const gfx::Rect& initial_pos,
                                    bool user_gesture) {
  if (!is_swapped_out_) {
    delegate_->ShowCreatedWindow(
        route_id, disposition, initial_pos, user_gesture);
  }
  Send(new ViewMsg_Move_ACK(route_id));
}
