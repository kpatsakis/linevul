void HTMLMediaElement::requestRemotePlaybackControl() {
  if (webMediaPlayer())
    webMediaPlayer()->requestRemotePlaybackControl();
}
