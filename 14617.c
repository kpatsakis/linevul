void Browser::NotifyTabOfFullscreenExitIfNecessary() {
  if (fullscreened_tab_)
    fullscreened_tab_->ExitFullscreenMode();
  fullscreened_tab_ = NULL;
  tab_caused_fullscreen_ = false;
}
