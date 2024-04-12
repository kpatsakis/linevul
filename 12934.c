void ShellSurface::UpdateWidgetBounds() {
  DCHECK(widget_);

  if (widget_->IsMaximized() || widget_->IsFullscreen() || IsResizing())
    return;

  if (!pending_configs_.empty() || scoped_configure_)
    return;

  gfx::Rect visible_bounds = GetVisibleBounds();
  gfx::Rect new_widget_bounds = visible_bounds;

  if (initial_bounds_.IsEmpty())
    new_widget_bounds.set_origin(widget_->GetNativeWindow()->bounds().origin());

  if (resize_component_ != HTCAPTION) {
    gfx::Point new_widget_origin =
        GetSurfaceOrigin() + visible_bounds.OffsetFromOrigin();
    aura::Window::ConvertPointToTarget(widget_->GetNativeWindow(),
                                       widget_->GetNativeWindow()->parent(),
                                       &new_widget_origin);
    new_widget_bounds.set_origin(new_widget_origin);
  }

  DCHECK(!ignore_window_bounds_changes_);
  ignore_window_bounds_changes_ = true;
  if (widget_->GetNativeWindow()->bounds() != new_widget_bounds)
    widget_->SetBounds(new_widget_bounds);
  ignore_window_bounds_changes_ = false;

  surface_->window()->SetBounds(
      gfx::Rect(GetSurfaceOrigin(), surface_->window()->layer()->size()));
}
