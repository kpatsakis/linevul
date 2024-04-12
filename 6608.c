void RenderFrameImpl::ForwardMessageToPortalHost(
    blink::TransferableMessage message,
    const url::Origin& source_origin,
    const base::Optional<url::Origin>& target_origin) {
  frame_->ForwardMessageToPortalHost(std::move(message), source_origin,
                                     target_origin);
}
