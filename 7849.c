void Document::DispatchFreezeEvent() {
  DCHECK(RuntimeEnabledFeatures::PageLifecycleEnabled());
  const TimeTicks freeze_event_start = CurrentTimeTicks();
  SetFreezingInProgress(true);
  DispatchEvent(Event::Create(EventTypeNames::freeze));
  SetFreezingInProgress(false);
  const TimeTicks freeze_event_end = CurrentTimeTicks();
  DEFINE_STATIC_LOCAL(CustomCountHistogram, freeze_histogram,
                      ("DocumentEventTiming.FreezeDuration", 0, 10000000, 50));
  freeze_histogram.Count(
      (freeze_event_end - freeze_event_start).InMicroseconds());
}
