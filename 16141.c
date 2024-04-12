ScopedPixelUnpackState::~ScopedPixelUnpackState() {
  state_->RestoreUnpackState();
}
