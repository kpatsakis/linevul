void Browser::TabDeactivated(TabContents* contents) {
  fullscreen_controller_->OnTabDeactivated(contents);
  search_delegate_->OnTabDeactivated(contents->web_contents());

  window_->GetLocationBar()->SaveStateToContents(contents->web_contents());
}
