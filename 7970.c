base::Optional<gfx::Size> WebContentsImpl::GetFullscreenVideoSize() {
  base::Optional<WebContentsObserver::MediaPlayerId> id =
      media_web_contents_observer_->GetFullscreenVideoMediaPlayerId();
  if (id && cached_video_sizes_.count(id.value()))
    return base::Optional<gfx::Size>(cached_video_sizes_[id.value()]);
  return base::Optional<gfx::Size>();
}
