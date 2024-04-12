static String ExtractSelectedText(const FrameSelection& selection,
                                  TextIteratorBehavior behavior) {
  const VisibleSelectionInFlatTree& visible_selection =
      selection.ComputeVisibleSelectionInFlatTree();
  const EphemeralRangeInFlatTree& range =
      visible_selection.ToNormalizedEphemeralRange();
  return PlainText(range, behavior).Replace(0, "");
}
