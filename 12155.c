BackingStore* RenderWidgetHostImpl::GetBackingStore(bool force_create) {
  if (!view_)
    return NULL;

  gfx::Size view_size = current_size_;
  if (!should_auto_resize_) {
    gfx::Rect view_rect = view_->GetViewBounds();
    if (view_rect.IsEmpty())
      return NULL;
    view_size = view_rect.size();
  }

  TRACE_EVENT2("renderer_host", "RenderWidgetHostImpl::GetBackingStore",
               "width", base::IntToString(view_size.width()),
               "height", base::IntToString(view_size.height()));

  DCHECK(!is_hidden_ || !force_create) <<
      "GetBackingStore called while hidden!";

  DCHECK(!in_get_backing_store_) << "GetBackingStore called recursively!";
  base::AutoReset<bool> auto_reset_in_get_backing_store(
      &in_get_backing_store_, true);

  BackingStore* backing_store = NULL;
  if (TryGetBackingStore(view_size, &backing_store) || !force_create)
    return backing_store;

  if (!repaint_ack_pending_ && !resize_ack_pending_ && !view_being_painted_) {
    repaint_start_time_ = TimeTicks::Now();
    repaint_ack_pending_ = true;
    Send(new ViewMsg_Repaint(routing_id_, view_size));
  }

  TimeDelta max_delay = TimeDelta::FromMilliseconds(kPaintMsgTimeoutMS);
  TimeTicks end_time = TimeTicks::Now() + max_delay;
  do {
    TRACE_EVENT0("renderer_host", "GetBackingStore::WaitForUpdate");

#if defined(OS_MACOSX)
    view_->AboutToWaitForBackingStoreMsg();
#endif

    IPC::Message msg;
    if (process_->WaitForBackingStoreMsg(routing_id_, max_delay, &msg)) {
      OnMessageReceived(msg);

      if (should_auto_resize_)
        view_size = current_size_;

      if (TryGetBackingStore(view_size, &backing_store) ||
          abort_get_backing_store_) {
        abort_get_backing_store_ = false;
        return backing_store;
      }
    } else {
      TRACE_EVENT0("renderer_host", "GetBackingStore::Timeout");
      break;
    }

    max_delay = end_time - TimeTicks::Now();
  } while (max_delay > TimeDelta::FromSeconds(0));

  if (view_size != current_size_)
    TryGetBackingStore(current_size_, &backing_store);
  return backing_store;
}
