void ClientControlledShellSurface::UpdateFrame() {
  if (!widget_)
    return;
  gfx::Rect work_area =
      display::Screen::GetScreen()
          ->GetDisplayNearestWindow(widget_->GetNativeWindow())
          .work_area();

  ash::wm::WindowState* window_state = GetWindowState();
  bool enable_wide_frame = GetFrameView()->GetVisible() &&
                           window_state->IsMaximizedOrFullscreenOrPinned() &&
                           work_area.width() != geometry().width();

  if (enable_wide_frame) {
    if (!wide_frame_) {
      wide_frame_ = std::make_unique<ash::WideFrameView>(widget_);
      ash::ImmersiveFullscreenController::EnableForWidget(widget_, false);
      wide_frame_->Init(immersive_fullscreen_controller_.get());
      wide_frame_->header_view()->GetFrameHeader()->SetFrameTextOverride(
          GetFrameView()
              ->GetHeaderView()
              ->GetFrameHeader()
              ->frame_text_override());
      wide_frame_->GetWidget()->Show();

      InstallCustomWindowTargeter();

      UpdateCaptionButtonModel();
    }
  } else {
    if (wide_frame_) {
      ash::ImmersiveFullscreenController::EnableForWidget(widget_, false);
      wide_frame_.reset();
      GetFrameView()->InitImmersiveFullscreenControllerForView(
          immersive_fullscreen_controller_.get());
      InstallCustomWindowTargeter();

      UpdateCaptionButtonModel();
    }
    UpdateFrameWidth();
  }
  UpdateAutoHideFrame();
}
