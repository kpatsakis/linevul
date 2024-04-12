void ThumbnailGenerator::WidgetDestroyed(RenderWidgetHost* widget) {
  EraseHostFromShownList(widget);
}
