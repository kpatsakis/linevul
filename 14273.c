void BrowserView::EnterFullscreen(const GURL& url,
                                  ExclusiveAccessBubbleType bubble_type) {
  if (IsFullscreen())
    return;  // Nothing to do.

  ProcessFullscreen(true, url, bubble_type);
}
