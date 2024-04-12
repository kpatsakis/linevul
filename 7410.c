void LocalFrame::DidResume() {
  DCHECK(RuntimeEnabledFeatures::PageLifecycleEnabled());
  if (GetDocument()) {
    const TimeTicks resume_event_start = CurrentTimeTicks();
    GetDocument()->DispatchEvent(Event::Create(EventTypeNames::resume));
    const TimeTicks resume_event_end = CurrentTimeTicks();
    DEFINE_STATIC_LOCAL(
        CustomCountHistogram, resume_histogram,
        ("DocumentEventTiming.ResumeDuration", 0, 10000000, 50));
    resume_histogram.Count(
        (resume_event_end - resume_event_start).InMicroseconds());
    if (auto* frame_resource_coordinator = GetFrameResourceCoordinator()) {
      frame_resource_coordinator->SetLifecycleState(
          resource_coordinator::mojom::LifecycleState::kRunning);
    }
  }
}
