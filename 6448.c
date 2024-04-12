void InputMethodController::SetCompositionFromExistingText(
    const Vector<CompositionUnderline>& underlines,
    unsigned composition_start,
    unsigned composition_end) {
  Element* editable = GetFrame()
                          .Selection()
                          .ComputeVisibleSelectionInDOMTreeDeprecated()
                          .RootEditableElement();
  if (!editable)
    return;

  DCHECK(!GetDocument().NeedsLayoutTreeUpdate());

  const EphemeralRange range =
      PlainTextRange(composition_start, composition_end).CreateRange(*editable);
  if (range.IsNull())
    return;

  const Position start = range.StartPosition();
  if (RootEditableElementOf(start) != editable)
    return;

  const Position end = range.EndPosition();
  if (RootEditableElementOf(end) != editable)
    return;

  Clear();

  AddCompositionUnderlines(underlines, editable, composition_start);

  has_composition_ = true;
  if (!composition_range_)
    composition_range_ = Range::Create(GetDocument());
  composition_range_->setStart(range.StartPosition());
  composition_range_->setEnd(range.EndPosition());
}
