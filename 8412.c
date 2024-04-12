void WebMediaPlayerImpl::EnableOverlay() {
  overlay_enabled_ = true;
  if (request_routing_token_cb_ &&
      overlay_mode_ == OverlayMode::kUseAndroidOverlay) {
    overlay_routing_token_is_pending_ = true;
    token_available_cb_.Reset(
        base::Bind(&WebMediaPlayerImpl::OnOverlayRoutingToken, AsWeakPtr()));
    request_routing_token_cb_.Run(token_available_cb_.callback());
  }

  if (decoder_requires_restart_for_overlay_)
    ScheduleRestart();
}
