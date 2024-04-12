bool Editor::tryDHTMLPaste(PasteMode pasteMode) {
  return !dispatchCPPEvent(EventTypeNames::paste, DataTransferReadable,
                           pasteMode);
}
