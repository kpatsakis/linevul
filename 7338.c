void RenderWidgetHostImpl::Blur() {
  if (IsMouseLocked())
    view_->UnlockMouse();

  Send(new ViewMsg_SetFocus(routing_id_, false));
}
