void Browser::ToggleFullscreenModeForTab(WebContents* web_contents,
                                         bool enter_fullscreen) {
  fullscreen_controller_->ToggleFullscreenModeForTab(web_contents,
                                                     enter_fullscreen);
}
