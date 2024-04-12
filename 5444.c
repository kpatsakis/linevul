bool Extension::ShouldDisplayInNewTabPage() const {
  return is_app() && display_in_new_tab_page_;
}
