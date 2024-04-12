static bool ExecuteSelectToMark(LocalFrame& frame,
                                Event*,
                                EditorCommandSource,
                                const String&) {
  const EphemeralRange mark =
      frame.GetEditor().Mark().ToNormalizedEphemeralRange();
  EphemeralRange selection = frame.GetEditor().SelectedRange();
  if (mark.IsNull() || selection.IsNull())
    return false;
  frame.Selection().SetSelection(
      SelectionInDOMTree::Builder()
          .SetBaseAndExtent(UnionEphemeralRanges(mark, selection))
          .Build(),
      FrameSelection::kCloseTyping);
  return true;
}
