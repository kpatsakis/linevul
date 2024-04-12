void AutocompleteEditModel::OnWillKillFocus(
    gfx::NativeView view_gaining_focus) {
  SetSuggestedText(string16(), INSTANT_COMPLETE_NOW);

  InstantController* instant = controller_->GetInstant();
  if (instant)
    instant->OnAutocompleteLostFocus(view_gaining_focus);
}
