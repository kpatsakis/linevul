void WebContentsViewAura::OnDragEntered(const ui::DropTargetEvent& event) {
  if (drag_dest_delegate_)
    drag_dest_delegate_->DragInitialize(web_contents_);

  current_drop_data_.reset(new DropData());

  PrepareDropData(current_drop_data_.get(), event.data());
  blink::WebDragOperationsMask op = ConvertToWeb(event.source_operations());

  gfx::Point screen_pt =
      gfx::Screen::GetScreenFor(GetNativeView())->GetCursorScreenPoint();
  current_rvh_for_drag_ = web_contents_->GetRenderViewHost();
  web_contents_->GetRenderViewHost()->DragTargetDragEnter(
      *current_drop_data_.get(), event.location(), screen_pt, op,
      ConvertAuraEventFlagsToWebInputEventModifiers(event.flags()));

  if (drag_dest_delegate_) {
    drag_dest_delegate_->OnReceiveDragData(event.data());
    drag_dest_delegate_->OnDragEnter();
  }
}
