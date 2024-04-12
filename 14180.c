void Performance::AddPaintTiming(PerformancePaintTiming::PaintType type,
                                 TimeTicks start_time) {
  if (!RuntimeEnabledFeatures::PerformancePaintTimingEnabled())
    return;

  PerformanceEntry* entry = new PerformancePaintTiming(
      type, MonotonicTimeToDOMHighResTimeStamp(start_time));
  if (type == PerformancePaintTiming::PaintType::kFirstPaint)
    first_paint_timing_ = entry;
  else if (type == PerformancePaintTiming::PaintType::kFirstContentfulPaint)
    first_contentful_paint_timing_ = entry;
  NotifyObserversOfEntry(*entry);
}
