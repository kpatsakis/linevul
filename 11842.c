void AutocompleteEditModel::ClearPopupKeywordMode() const {
  if (popup_->IsOpen() &&
      popup_->selected_line_state() == AutocompletePopupModel::KEYWORD)
    popup_->SetSelectedLineState(AutocompletePopupModel::NORMAL);
}
