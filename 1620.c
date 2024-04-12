WebMediaPlayer::DisplayType HTMLMediaElement::DisplayType() const {
  return IsFullscreen() ? WebMediaPlayer::DisplayType::kFullscreen
                        : WebMediaPlayer::DisplayType::kInline;
}
