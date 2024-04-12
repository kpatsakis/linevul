void BrowserView::UpdateExclusiveAccessExitBubbleContent(
    const GURL& url,
    ExclusiveAccessBubbleType bubble_type,
    ExclusiveAccessBubbleHideCallback bubble_first_hide_callback,
    bool force_update) {
  if (bubble_type == EXCLUSIVE_ACCESS_BUBBLE_TYPE_NONE ||
      (ShouldUseImmersiveFullscreenForUrl(url) &&
       !profiles::IsPublicSession())) {
    exclusive_access_bubble_.reset();
    if (bubble_first_hide_callback) {
      std::move(bubble_first_hide_callback)
          .Run(ExclusiveAccessBubbleHideReason::kNotShown);
    }
    return;
  }

  if (exclusive_access_bubble_) {
    exclusive_access_bubble_->UpdateContent(
        url, bubble_type, std::move(bubble_first_hide_callback), force_update);
    return;
  }

  exclusive_access_bubble_.reset(new ExclusiveAccessBubbleViews(
      this, url, bubble_type, std::move(bubble_first_hide_callback)));
}
