void MediaControlFullscreenButtonElement::setIsFullscreen(bool isFullscreen) {
  setDisplayType(isFullscreen ? MediaExitFullscreenButton
                              : MediaEnterFullscreenButton);
}
