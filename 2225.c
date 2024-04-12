void DidVisibilityChange(LayerTreeHostImpl* id, bool visible) {
  if (visible) {
    TRACE_EVENT_ASYNC_BEGIN1("cc", "LayerTreeHostImpl::SetVisible", id,
                             "LayerTreeHostImpl", id);
    return;
  }

  TRACE_EVENT_ASYNC_END0("cc", "LayerTreeHostImpl::SetVisible", id);
}
