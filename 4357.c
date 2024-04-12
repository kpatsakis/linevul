void RenderThread::RemoveRoute(int32 routing_id) {
  widget_count_--;
  return ChildThread::RemoveRoute(routing_id);
}
