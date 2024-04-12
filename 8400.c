RenderWidgetHost* RenderWidgetHost::FromID(
    int32_t process_id,
    int32_t routing_id) {
  return RenderWidgetHostImpl::FromID(process_id, routing_id);
}
