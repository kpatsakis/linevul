static bool ExecuteMoveWordForward(LocalFrame& frame,
                                   Event*,
                                   EditorCommandSource,
                                   const String&) {
  frame.Selection().Modify(SelectionModifyAlteration::kMove,
                           SelectionModifyDirection::kForward,
                           TextGranularity::kWord, SetSelectionBy::kUser);
  return true;
}
