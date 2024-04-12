bool OmniboxViewViews::HandleAccessibleAction(
    const ui::AXActionData& action_data) {
  if (read_only())
    return Textfield::HandleAccessibleAction(action_data);

  if (action_data.action == ui::AX_ACTION_SET_VALUE) {
    SetUserText(action_data.value, true);
    return true;
  } else if (action_data.action == ui::AX_ACTION_REPLACE_SELECTED_TEXT) {
    model()->SetInputInProgress(true);
    if (saved_selection_for_focus_change_.IsValid()) {
      SelectRange(saved_selection_for_focus_change_);
      saved_selection_for_focus_change_ = gfx::Range::InvalidRange();
    }
    InsertOrReplaceText(action_data.value);
    TextChanged();
    return true;
  }

  return Textfield::HandleAccessibleAction(action_data);
}
