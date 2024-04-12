StartupTimeBomb::~StartupTimeBomb() {
  DCHECK(this == g_startup_timebomb_);
  DCHECK_EQ(thread_id_, base::PlatformThread::CurrentId());
  if (startup_watchdog_)
    Disarm();
  g_startup_timebomb_ = nullptr;
}
