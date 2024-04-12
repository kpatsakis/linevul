void Document::BeginLifecycleUpdatesIfRenderingReady() {
  if (!IsActive())
    return;
  if (!IsRenderingReady())
    return;
  View()->BeginLifecycleUpdates();
}
