void HTMLMediaElement::enterPictureInPicture(
    WebMediaPlayer::PipWindowSizeCallback callback) {
  if (GetWebMediaPlayer())
    GetWebMediaPlayer()->EnterPictureInPicture(std::move(callback));
}
