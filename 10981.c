void ThumbnailGenerator::EraseHostFromShownList(RenderWidgetHost* widget) {
  std::vector<RenderWidgetHost*>::iterator found =
      std::find(shown_hosts_.begin(), shown_hosts_.end(), widget);
  if (found != shown_hosts_.end())
    shown_hosts_.erase(found);
}
