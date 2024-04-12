bool Document::IsDelayingLoadEvent() {
  if (ThreadState::Current()->SweepForbidden()) {
    if (!load_event_delay_count_)
      CheckLoadEventSoon();
    return true;
  }
  return load_event_delay_count_;
}
