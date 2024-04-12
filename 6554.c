void WebMediaPlayerImpl::ExitPictureInPicture(
    blink::WebMediaPlayer::PipWindowClosedCallback callback) {
  delegate_->DidPictureInPictureModeEnd(delegate_id_, std::move(callback));

  OnPictureInPictureModeEnded();
}
