void Editor::respondToChangedSelection(
    const Position& oldSelectionStart,
    FrameSelection::SetSelectionOptions options) {
  spellChecker().respondToChangedSelection(oldSelectionStart, options);
  client().respondToChangedSelection(&frame(),
                                     frame()
                                         .selection()
                                         .selectionInDOMTree()
                                         .selectionTypeWithLegacyGranularity());
  setStartNewKillRingSequence(true);
}
