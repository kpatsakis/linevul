void HTMLMediaElement::DeferLoad() {
  DCHECK(!deferred_load_timer_.IsActive());
  DCHECK_EQ(deferred_load_state_, kNotDeferred);
  ChangeNetworkStateFromLoadingToIdle();
  deferred_load_timer_.StartOneShot(TimeDelta(), FROM_HERE);
  deferred_load_state_ = kWaitingForStopDelayingLoadEventTask;
}
