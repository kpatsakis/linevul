void SessionService::RecordUpdatedSaveTime(base::TimeDelta delta,
                                           bool use_long_period) {
  std::string name("SessionRestore.SavePeriod");
  UMA_HISTOGRAM_CUSTOM_TIMES(name,
      delta,
      save_delay_in_millis_,
      save_delay_in_mins_,
      50);
  if (use_long_period) {
    std::string long_name_("SessionRestore.SaveLongPeriod");
    UMA_HISTOGRAM_CUSTOM_TIMES(long_name_,
        delta,
        save_delay_in_mins_,
        save_delay_in_hrs_,
        50);
  }
}
