gfx::Rect BrowserWindowGtk::GetInstantBounds() {
  return ui::GetWidgetScreenBounds(contents_container_->widget());
}
