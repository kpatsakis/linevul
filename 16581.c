void AppListController::OnSigninStatusChanged() {
  if (current_view_)
    current_view_->OnSigninStatusChanged();
}
