void Editor::pasteAsPlainText(EditorCommandSource source) {
  if (tryDHTMLPaste(PlainTextOnly))
    return;
  if (!canPaste())
    return;
  spellChecker().updateMarkersForWordsAffectedByEditing(false);
  pasteAsPlainTextWithPasteboard(Pasteboard::generalPasteboard());
}
