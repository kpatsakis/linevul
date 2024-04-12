bool Textfield::PasteSelectionClipboard() {
  DCHECK(performing_user_action_);
  DCHECK(!read_only());
  const base::string16 selection_clipboard_text = GetSelectionClipboardText();
  if (selection_clipboard_text.empty())
    return false;

  model_->InsertText(selection_clipboard_text);
  return true;
}
