void HTMLMediaElement::OnViewportIntersectionChanged(
    const HeapVector<Member<IntersectionObserverEntry>>& entries) {
  const bool is_mostly_filling_viewport =
      (entries.back()->intersectionRatio() >= kMostlyFillViewportThreshold);
  if (mostly_filling_viewport_ == is_mostly_filling_viewport)
    return;

  mostly_filling_viewport_ = is_mostly_filling_viewport;
  if (web_media_player_)
    web_media_player_->BecameDominantVisibleContent(mostly_filling_viewport_);
}
