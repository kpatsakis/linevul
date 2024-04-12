void BrowserLauncherItemController::UpdateItemStatus() {
  ash::LauncherItemStatus status;
  if (ash::wm::IsActiveWindow(window_)) {
    if (window_->GetProperty(aura::client::kDrawAttentionKey))
      window_->SetProperty(aura::client::kDrawAttentionKey, false);
    status = ash::STATUS_ACTIVE;
  } else if (window_->GetProperty(aura::client::kDrawAttentionKey)) {
    status = ash::STATUS_ATTENTION;
  } else {
    status = ash::STATUS_RUNNING;
  }
  launcher_controller()->SetItemStatus(launcher_id(), status);
}
