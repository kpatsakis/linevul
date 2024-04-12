void RenderWidgetHostImpl::OnMsgUpdateIsDelayed() {
  if (in_get_backing_store_)
    abort_get_backing_store_ = true;
}
