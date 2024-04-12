void WebContentsImpl::OnMediaSessionStateChanged() {
  MediaSession* session = MediaSession::Get(this);
  FOR_EACH_OBSERVER(WebContentsObserver, observers_,
                    MediaSessionStateChanged(session->IsControllable(),
                                             session->IsSuspended()));
}
