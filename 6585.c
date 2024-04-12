bool OmniboxViewViews::OnAfterPossibleChange(bool allow_keyword_ui_change) {
  State new_state;
  GetState(&new_state);
  OmniboxView::StateChanges state_changes =
      GetStateChanges(state_before_change_, new_state);

  state_changes.text_differs =
      state_changes.text_differs ||
      (ime_composing_before_change_ != IsIMEComposing());

  const bool something_changed = model()->OnAfterPossibleChange(
      state_changes, allow_keyword_ui_change && !IsIMEComposing());

  if (something_changed &&
      (state_changes.text_differs || state_changes.keyword_differs))
    TextChanged();
  else if (state_changes.selection_differs)
    EmphasizeURLComponents();
  else if (delete_at_end_pressed_)
    model()->OnChanged();

  return something_changed;
}
