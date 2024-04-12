void RTCPeerConnectionHandler::AddTransceiverWithTrackOnSignalingThread(
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> webrtc_track,
    webrtc::RtpTransceiverInit init,
    TransceiverStateSurfacer* transceiver_state_surfacer,
    webrtc::RTCErrorOr<rtc::scoped_refptr<webrtc::RtpTransceiverInterface>>*
        error_or_transceiver) {
  *error_or_transceiver =
      native_peer_connection_->AddTransceiver(webrtc_track, init);
  std::vector<rtc::scoped_refptr<webrtc::RtpTransceiverInterface>> transceivers;
  if (error_or_transceiver->ok())
    transceivers.push_back(error_or_transceiver->value());
  transceiver_state_surfacer->Initialize(track_adapter_map_, transceivers);
}
