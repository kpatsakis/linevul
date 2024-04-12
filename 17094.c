void TitleWatcher::TestTitle() {
  const base::string16& current_title = web_contents()->GetTitle();
  if (base::ContainsValue(expected_titles_, current_title)) {
    observed_title_ = current_title;
    run_loop_.Quit();
  }
}
