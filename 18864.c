void FrameSelection::FocusedOrActiveStateChanged() {
  bool active_and_focused = FrameIsFocusedAndActive();

  if (Element* element = GetDocument().FocusedElement())
    element->FocusStateChanged();

  GetDocument().UpdateStyleAndLayoutTree();

  LayoutViewItem view = GetDocument().GetLayoutViewItem();
  if (!view.IsNull())
    layout_selection_->InvalidatePaintForSelection();

  if (active_and_focused)
    SetSelectionFromNone();
  else
    frame_->GetSpellChecker().SpellCheckAfterBlur();
  frame_caret_->SetCaretVisibility(active_and_focused
                                       ? CaretVisibility::kVisible
                                       : CaretVisibility::kHidden);

  frame_->GetEventHandler().CapsLockStateMayHaveChanged();

  if (use_secure_keyboard_entry_when_active_)
    SetUseSecureKeyboardEntry(active_and_focused);
}
