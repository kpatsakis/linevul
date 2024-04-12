bool HTMLMediaElement::HasVideo() const {
  return GetWebMediaPlayer() && GetWebMediaPlayer()->HasVideo();
}
