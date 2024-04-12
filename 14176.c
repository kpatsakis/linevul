void HTMLMediaElement::DeferredLoadTimerFired(TimerBase*) {
  SetShouldDelayLoadEvent(false);

  if (deferred_load_state_ == kExecuteOnStopDelayingLoadEventTask) {
    ExecuteDeferredLoad();
    return;
  }
  DCHECK_EQ(deferred_load_state_, kWaitingForStopDelayingLoadEventTask);
  deferred_load_state_ = kWaitingForTrigger;
}
