inline void FrameLoader::TakeObjectSnapshot() const {
  if (detached_) {
    return;
  }
  TRACE_EVENT_OBJECT_SNAPSHOT_WITH_ID("loading", "FrameLoader", this,
                                      ToTracedValue());
}
