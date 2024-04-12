static bool ExecuteMoveParagraphBackwardAndModifySelection(LocalFrame& frame,
                                                           Event*,
                                                           EditorCommandSource,
                                                           const String&) {
  frame.Selection().Modify(SelectionModifyAlteration::kExtend,
                           SelectionModifyDirection::kBackward,
                           TextGranularity::kParagraph, SetSelectionBy::kUser);
  return true;
}
