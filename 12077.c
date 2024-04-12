void RTCPeerConnectionHandler::GetStats(
    std::unique_ptr<blink::WebRTCStatsReportCallback> callback,
    blink::RTCStatsFilter filter) {
  DCHECK(task_runner_->RunsTasksInCurrentSequence());
  signaling_thread()->PostTask(
      FROM_HERE,
      base::BindOnce(&GetRTCStatsOnSignalingThread, task_runner_,
                     native_peer_connection_, std::move(callback), filter));
}
