void Browser::UpdateSearchState(TabContents* contents) {
  if (chrome::search::IsInstantExtendedAPIEnabled(profile_))
    search_delegate_->OnTabActivated(contents->web_contents());
}
