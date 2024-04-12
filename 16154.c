void Editor::RevealSelectionAfterEditingOperation(
    const ScrollAlignment& alignment,
    RevealExtentOption reveal_extent_option) {
  if (prevent_reveal_selection_)
    return;
  if (!GetFrame().Selection().IsAvailable())
    return;
   GetFrame().Selection().RevealSelection(alignment, reveal_extent_option);
 }
