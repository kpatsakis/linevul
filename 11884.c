void RenderFrameImpl::OnSetOverlayRoutingToken(
    const base::UnguessableToken& token) {
  overlay_routing_token_ = token;
  for (const auto& cb : pending_routing_token_callbacks_)
    cb.Run(overlay_routing_token_.value());
  pending_routing_token_callbacks_.clear();
}
