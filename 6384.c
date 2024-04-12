bool BrowserView::GetSavedWindowPlacement(
    gfx::Rect* bounds,
    ui::WindowShowState* show_state) const {
  if (!ShouldSaveOrRestoreWindowPos())
    return false;
  chrome::GetSavedWindowBoundsAndShowState(browser_.get(), bounds, show_state);

#if defined(USE_ASH)
  if (browser_->is_type_popup() || browser_->is_type_panel()) {
    if (bounds->x() == 0 && bounds->y() == 0) {
      *bounds = ChromeShellDelegate::instance()->window_positioner()->
          GetPopupPosition(*bounds);
    }
  }
#endif

  if ((browser_->is_type_popup() &&
       !browser_->is_devtools() && !browser_->is_app()) ||
      (browser_->is_type_panel())) {
    if (IsToolbarVisible()) {
      bounds->set_height(
          bounds->height() + toolbar_->GetPreferredSize().height());
    }

    gfx::Rect window_rect = frame_->non_client_view()->
        GetWindowBoundsForClientBounds(*bounds);
    window_rect.set_origin(bounds->origin());

    if (window_rect.x() == 0 && window_rect.y() == 0) {
      gfx::Size size = window_rect.size();
      window_rect.set_origin(
          WindowSizer::GetDefaultPopupOrigin(size,
                                             browser_->host_desktop_type()));
    }

    *bounds = window_rect;
    *show_state = ui::SHOW_STATE_NORMAL;
  }

  return true;
}
