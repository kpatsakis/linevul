base::TimeDelta SyncerProtoUtil::GetThrottleDelay(
    const sync_pb::ClientToServerResponse& response) {
  base::TimeDelta throttle_delay =
      base::TimeDelta::FromSeconds(kSyncDelayAfterThrottled);
  if (response.has_client_command()) {
    const sync_pb::ClientCommand& command = response.client_command();
    if (command.has_throttle_delay_seconds()) {
      throttle_delay =
          base::TimeDelta::FromSeconds(command.throttle_delay_seconds());
    }
  }
  return throttle_delay;
}
