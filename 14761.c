base::Optional<gfx::Rect> ClientControlledShellSurface::GetWidgetBounds()
    const {
  const ash::NonClientFrameViewAsh* frame_view = GetFrameView();
  if (frame_view->GetVisible()) {
    return frame_view->GetWindowBoundsForClientBounds(GetVisibleBounds());
  }

  return GetVisibleBounds();
}
