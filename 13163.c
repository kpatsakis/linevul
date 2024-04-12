RenderWidgetHostInputEventRouter* WebContentsImpl::GetInputEventRouter() {
  if (!is_being_destroyed_ && GetOuterWebContents())
    return GetOuterWebContents()->GetInputEventRouter();

  if (!rwh_input_event_router_.get() && !is_being_destroyed_)
    rwh_input_event_router_.reset(new RenderWidgetHostInputEventRouter);
  return rwh_input_event_router_.get();
}
