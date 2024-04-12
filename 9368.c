void BrowserWindowGtk::UpdateFullscreenExitBubbleContent(
     const GURL& url,
      FullscreenExitBubbleType bubble_type) {
  if (bubble_type == FEB_TYPE_NONE) {
   fullscreen_exit_bubble_.reset();
  } else if (fullscreen_exit_bubble_.get()) {
   fullscreen_exit_bubble_->UpdateContent(url, bubble_type);
  } else {
    fullscreen_exit_bubble_.reset(new FullscreenExitBubbleGtk(
        GTK_FLOATING_CONTAINER(render_area_floating_container_),
        browser(),
        url,
        bubble_type));
  }
}
