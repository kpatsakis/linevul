void RenderFrameImpl::InitializeUserMediaClient() {
  RenderThreadImpl* render_thread = RenderThreadImpl::current();
  if (!render_thread)  // Will be NULL during unit tests.
    return;

#if BUILDFLAG(ENABLE_WEBRTC)
  DCHECK(!web_user_media_client_);
  web_user_media_client_ = new UserMediaClientImpl(
      this, RenderThreadImpl::current()->GetPeerConnectionDependencyFactory(),
      std::make_unique<MediaStreamDeviceObserver>(this));
#endif
}
