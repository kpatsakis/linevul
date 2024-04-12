void HeadlessWebContentsImpl::OnNeedsExternalBeginFrames(
    bool needs_begin_frames) {
  TRACE_EVENT1("headless",
               "HeadlessWebContentsImpl::OnNeedsExternalBeginFrames",
               "needs_begin_frames", needs_begin_frames);

  needs_external_begin_frames_ = needs_begin_frames;
  for (int session_id : begin_frame_events_enabled_sessions_)
    SendNeedsBeginFramesEvent(session_id);
}
