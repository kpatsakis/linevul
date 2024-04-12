void NetworkThrottleManagerImpl::RecomputeOutstanding() {
  base::TimeTicks now(tick_clock_->NowTicks());
  base::TimeDelta age_horizon(base::TimeDelta::FromMilliseconds((
      kMedianLifetimeMultiple * lifetime_median_estimate_.current_estimate())));
  while (!outstanding_throttles_.empty()) {
    ThrottleImpl* throttle = *outstanding_throttles_.begin();
    if (throttle->start_time() + age_horizon >= now)
      break;

    outstanding_throttles_.erase(outstanding_throttles_.begin());
    throttle->SetAged();
    throttle->set_queue_pointer(outstanding_throttles_.end());
  }

  if (outstanding_throttles_.empty())
    return;

  if (outstanding_recomputation_timer_->IsRunning())
    return;

  ThrottleImpl* first_throttle(*outstanding_throttles_.begin());
  DCHECK_GE(first_throttle->start_time() + age_horizon, now);

  outstanding_recomputation_timer_->Start(
      FROM_HERE,
      ((first_throttle->start_time() + age_horizon) - now +
       base::TimeDelta::FromMilliseconds(kTimerFudgeInMs)),
      base::Bind(&NetworkThrottleManagerImpl::MaybeUnblockThrottles,
                 base::Unretained(this)));
}
