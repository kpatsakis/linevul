bool NeedsIncrementalInsertion(const LocalFrame& frame,
                               const String& new_text) {
  if (!frame.GetEditor().CanEditRichly())
    return false;

  if (frame.SelectedText().IsEmpty() || new_text.IsEmpty())
    return false;

  return true;
}
