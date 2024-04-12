gfx::Point ShellSurface::GetSurfaceOrigin() const {
  gfx::Rect window_bounds = widget_->GetNativeWindow()->bounds();

  if (!initial_bounds_.IsEmpty())
    return initial_bounds_.origin() - window_bounds.OffsetFromOrigin();

  gfx::Rect visible_bounds = GetVisibleBounds();
  switch (resize_component_) {
    case HTCAPTION:
      return origin_ - visible_bounds.OffsetFromOrigin();
    case HTBOTTOM:
    case HTRIGHT:
    case HTBOTTOMRIGHT:
      return gfx::Point() - visible_bounds.OffsetFromOrigin();
    case HTTOP:
    case HTTOPRIGHT:
      return gfx::Point(0, window_bounds.height() - visible_bounds.height()) -
             visible_bounds.OffsetFromOrigin();
      break;
    case HTLEFT:
    case HTBOTTOMLEFT:
      return gfx::Point(window_bounds.width() - visible_bounds.width(), 0) -
             visible_bounds.OffsetFromOrigin();
    case HTTOPLEFT:
      return gfx::Point(window_bounds.width() - visible_bounds.width(),
                        window_bounds.height() - visible_bounds.height()) -
             visible_bounds.OffsetFromOrigin();
    default:
      NOTREACHED();
      return gfx::Point();
  }
}
