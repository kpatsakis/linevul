void InputMethodController::DeleteSurroundingTextInCodePoints(int before,
                                                              int after) {
  DCHECK_GE(before, 0);
  DCHECK_GE(after, 0);
  if (!GetEditor().CanEdit())
    return;
  const PlainTextRange selection_offsets(GetSelectionOffsets());
  if (selection_offsets.IsNull())
    return;
  Element* const root_editable_element =
      GetFrame().Selection().RootEditableElementOrDocumentElement();
  if (!root_editable_element)
    return;

  const TextIteratorBehavior& behavior =
      TextIteratorBehavior::Builder()
          .SetEmitsObjectReplacementCharacter(true)
          .Build();
  const String& text = PlainText(
      EphemeralRange::RangeOfContents(*root_editable_element), behavior);

  if (text.Is8Bit())
    return DeleteSurroundingText(before, after);

  const int selection_start = static_cast<int>(selection_offsets.Start());
  const int selection_end = static_cast<int>(selection_offsets.End());

  const int before_length =
      CalculateBeforeDeletionLengthsInCodePoints(text, before, selection_start);
  if (IsInvalidDeletionLength(before_length))
    return;
  const int after_length =
      CalculateAfterDeletionLengthsInCodePoints(text, after, selection_end);
  if (IsInvalidDeletionLength(after_length))
    return;

  return DeleteSurroundingText(before_length, after_length);
}
