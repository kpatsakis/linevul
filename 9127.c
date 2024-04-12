bool BrowserView::GetSavedWindowPlacement(
    const views::Widget* widget,
    gfx::Rect* bounds,
    ui::WindowShowState* show_state) const {
  chrome::GetSavedWindowBoundsAndShowState(browser_.get(), bounds, show_state);

  if (chrome::SavedBoundsAreContentBounds(browser_.get())) {
    if (IsToolbarVisible()) {
      bounds->set_height(
          bounds->height() + toolbar_->GetPreferredSize().height());
    }

    gfx::Rect window_rect = frame_->non_client_view()->
        GetWindowBoundsForClientBounds(*bounds);
    window_rect.set_origin(bounds->origin());

    if (window_rect.x() == 0 && window_rect.y() == 0) {
      gfx::Size size = window_rect.size();
      window_rect.set_origin(WindowSizer::GetDefaultPopupOrigin(size));
    }

    *bounds = window_rect;
    *show_state = ui::SHOW_STATE_NORMAL;
  }

  return true;
}
