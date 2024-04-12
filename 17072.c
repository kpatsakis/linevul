void UserCloudPolicyManagerChromeOS::StartRefreshSchedulerIfReady() {
  if (core()->refresh_scheduler())
    return;  // Already started.

  if (wait_for_policy_fetch_)
    return;  // Still waiting for the initial, blocking fetch.

  if (!service() || !local_state_)
    return;  // Not connected.

  if (component_policy_service() &&
      !component_policy_service()->is_initialized()) {
    return;
  }

  core()->StartRefreshScheduler();
  core()->TrackRefreshDelayPref(local_state_,
                                policy_prefs::kUserPolicyRefreshRate);
}
