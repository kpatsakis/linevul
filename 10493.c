void AppListController::DismissAppList() {
  if (IsAppListVisible() && can_close_app_list_) {
    current_view_->GetWidget()->Hide();
    timer_.Stop();
    FreeAnyKeepAliveForView();
  }
}
