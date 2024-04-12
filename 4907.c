void TraceEvent::Reset() {
  duration_ = TimeDelta::FromInternalValue(-1);
  parameter_copy_storage_ = NULL;
  for (int i = 0; i < kTraceMaxNumArgs; ++i)
    convertable_values_[i] = NULL;
}
