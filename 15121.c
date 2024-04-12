void Performance::clearMarks(const String& mark_name) {
  if (!user_timing_)
    user_timing_ = UserTiming::Create(*this);
  user_timing_->ClearMarks(mark_name);
}
