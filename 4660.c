void HTMLMediaElement::setPreload(const AtomicString& preload) {
  BLINK_MEDIA_LOG << "setPreload(" << (void*)this << ", " << preload << ")";
  if (GetLoadType() == WebMediaPlayer::kLoadTypeMediaStream)
    return;
  setAttribute(kPreloadAttr, preload);
}
