void RTCPeerConnectionHandler::OnModifyTransceivers(
    std::vector<RtpTransceiverState> transceiver_states,
    bool is_remote_description) {
  DCHECK_EQ(configuration_.sdp_semantics, webrtc::SdpSemantics::kUnifiedPlan);
  std::vector<std::unique_ptr<blink::WebRTCRtpTransceiver>> web_transceivers(
      transceiver_states.size());
  PeerConnectionTracker::TransceiverUpdatedReason update_reason =
      !is_remote_description ? PeerConnectionTracker::TransceiverUpdatedReason::
                                   kSetLocalDescription
                             : PeerConnectionTracker::TransceiverUpdatedReason::
                                   kSetRemoteDescription;
  for (size_t i = 0; i < transceiver_states.size(); ++i) {
    uintptr_t transceiver_id = RTCRtpTransceiver::GetId(
        transceiver_states[i].webrtc_transceiver().get());
    auto it = FindTransceiver(transceiver_id);
    bool transceiver_is_new = (it == rtp_transceivers_.end());
    bool transceiver_was_modified = false;
    if (!transceiver_is_new) {
      const auto& previous_state = (*it)->state();
      transceiver_was_modified =
          previous_state.mid() != transceiver_states[i].mid() ||
          previous_state.stopped() != transceiver_states[i].stopped() ||
          previous_state.direction() != transceiver_states[i].direction() ||
          previous_state.current_direction() !=
              transceiver_states[i].current_direction();
    }

    web_transceivers[i] =
        CreateOrUpdateTransceiver(std::move(transceiver_states[i]));

    if (peer_connection_tracker_ &&
        (transceiver_is_new || transceiver_was_modified)) {
      size_t transceiver_index = GetTransceiverIndex(*web_transceivers[i]);
      if (transceiver_is_new) {
        peer_connection_tracker_->TrackAddTransceiver(
            this, update_reason, *web_transceivers[i].get(), transceiver_index);
      } else if (transceiver_was_modified) {
        peer_connection_tracker_->TrackModifyTransceiver(
            this, update_reason, *web_transceivers[i].get(), transceiver_index);
      }
    }
  }
  if (!is_closed_) {
    client_->DidModifyTransceivers(std::move(web_transceivers),
                                   is_remote_description);
  }
}
