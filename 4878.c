HTMLDialogElement* Document::ActiveModalDialog() const {
  for (auto it = top_layer_elements_.rbegin(); it != top_layer_elements_.rend();
       ++it) {
    if (auto* dialog = ToHTMLDialogElementOrNull(*it))
      return dialog;
  }

  return nullptr;
}
