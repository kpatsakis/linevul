void TabStripGtk::StopAnimation() {
  if (active_animation_.get())
    active_animation_->Stop();
}
