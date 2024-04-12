void Performance::mark(
    ScriptState* script_state,
    const String& mark_name,
    DoubleOrPerformanceMarkOptions& start_time_or_mark_options,
    ExceptionState& exception_state) {
  if (!RuntimeEnabledFeatures::CustomUserTimingEnabled()) {
    DCHECK(start_time_or_mark_options.IsNull());
  }

  if (!user_timing_)
    user_timing_ = UserTiming::Create(*this);

  DOMHighResTimeStamp start = 0.0;
  if (start_time_or_mark_options.IsDouble()) {
    start = start_time_or_mark_options.GetAsDouble();
  } else if (start_time_or_mark_options.IsPerformanceMarkOptions() &&
             start_time_or_mark_options.GetAsPerformanceMarkOptions()
                 .hasStartTime()) {
    start =
        start_time_or_mark_options.GetAsPerformanceMarkOptions().startTime();
  } else {
    start = now();
  }

  ScriptValue detail = ScriptValue::CreateNull(script_state);
  if (start_time_or_mark_options.IsPerformanceMarkOptions()) {
    detail = start_time_or_mark_options.GetAsPerformanceMarkOptions().detail();
  }

  if (PerformanceEntry* entry = user_timing_->Mark(
          script_state, mark_name, start, detail, exception_state))
    NotifyObserversOfEntry(*entry);
}
