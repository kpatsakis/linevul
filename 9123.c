static bool ExecuteMoveLeft(LocalFrame& frame,
                            Event*,
                            EditorCommandSource,
                            const String&) {
  return frame.Selection().Modify(
      SelectionModifyAlteration::kMove, SelectionModifyDirection::kLeft,
      TextGranularity::kCharacter, SetSelectionBy::kUser);
}
