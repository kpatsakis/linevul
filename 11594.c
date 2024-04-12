void RenderViewImpl::EnsureMediaStreamImpl() {
#if defined(ENABLE_P2P_APIS)
  if (!p2p_socket_dispatcher_)
    p2p_socket_dispatcher_ = new content::P2PSocketDispatcher(this);
#endif

#if defined(ENABLE_WEBRTC)
  if (!media_stream_dispatcher_)
    media_stream_dispatcher_ = new MediaStreamDispatcher(this);

  if (!media_stream_impl_.get()) {
    MediaStreamDependencyFactory* factory = new MediaStreamDependencyFactory();
    media_stream_impl_ = new MediaStreamImpl(
        media_stream_dispatcher_,
        p2p_socket_dispatcher_,
        RenderThreadImpl::current()->video_capture_impl_manager(),
        factory);
  }
#endif
}
