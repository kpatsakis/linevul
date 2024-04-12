void Automation::MouseButtonUp(int tab_id,
                               const gfx::Point& p,
                               Error** error) {
  *error = CheckAdvancedInteractionsSupported();
  if (*error)
    return;

  int windex = 0, tab_index = 0;
  *error = GetIndicesForTab(tab_id, &windex, &tab_index);
  if (*error)
    return;

  std::string error_msg;
  if (!SendMouseButtonUpJSONRequest(
          automation(), windex, tab_index, p.x(), p.y(), &error_msg)) {
    *error = new Error(kUnknownError, error_msg);
  }
}
