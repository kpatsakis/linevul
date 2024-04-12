void HTMLMediaElement::SetIgnorePreloadNone() {
  BLINK_MEDIA_LOG << "setIgnorePreloadNone(" << (void*)this << ")";
  ignore_preload_none_ = true;
  SetPlayerPreload();
}
