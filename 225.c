void GetRTCStatsOnSignalingThread(
    const scoped_refptr<base::SingleThreadTaskRunner>& main_thread,
    scoped_refptr<webrtc::PeerConnectionInterface> native_peer_connection,
    std::unique_ptr<blink::WebRTCStatsReportCallback> callback,
    blink::RTCStatsFilter filter) {
  TRACE_EVENT0("webrtc", "GetRTCStatsOnSignalingThread");

  native_peer_connection->GetStats(RTCStatsCollectorCallbackImpl::Create(
      main_thread, std::move(callback), filter));
}
