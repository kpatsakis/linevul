  size_t GetAndResetProcessedTouchEventCount() {
    size_t count = processed_touch_event_count_;
    processed_touch_event_count_ = 0;
    return count;
  }
