TabVisibility ContentVisibilityToRCVisibility(content::Visibility visibility) {
  if (visibility == content::Visibility::VISIBLE)
    return TabVisibility::kForeground;
  return TabVisibility::kBackground;
}
