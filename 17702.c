void WebMediaPlayerImpl::ForceStaleStateForTesting(ReadyState target_state) {
  stale_state_override_for_testing_.emplace(target_state);
  UpdatePlayState();
}
