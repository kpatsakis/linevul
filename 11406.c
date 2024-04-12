void TypingCommand::forwardDeleteKeyPressed(TextGranularity granularity,
                                            bool killRing,
                                            EditingState* editingState) {
  LocalFrame* frame = document().frame();
  if (!frame)
    return;

  frame->spellChecker().updateMarkersForWordsAffectedByEditing(false);

  VisibleSelection selectionToDelete;
  VisibleSelection selectionAfterUndo;

  switch (endingSelection().getSelectionType()) {
    case RangeSelection:
      selectionToDelete = endingSelection();
      selectionAfterUndo = selectionToDelete;
      break;
    case CaretSelection: {
      m_smartDelete = false;
      document().updateStyleAndLayoutIgnorePendingStylesheets();

      SelectionModifier selectionModifier(*frame, endingSelection());
      selectionModifier.modify(FrameSelection::AlterationExtend,
                               DirectionForward, granularity);
      if (killRing && selectionModifier.selection().isCaret() &&
          granularity != CharacterGranularity)
        selectionModifier.modify(FrameSelection::AlterationExtend,
                                 DirectionForward, CharacterGranularity);

      Position downstreamEnd =
          mostForwardCaretPosition(endingSelection().end());
      VisiblePosition visibleEnd = endingSelection().visibleEnd();
      Node* enclosingTableCell =
          enclosingNodeOfType(visibleEnd.deepEquivalent(), &isTableCell);
      if (enclosingTableCell &&
          visibleEnd.deepEquivalent() ==
              VisiblePosition::lastPositionInNode(enclosingTableCell)
                  .deepEquivalent())
        return;
      if (visibleEnd.deepEquivalent() ==
          endOfParagraph(visibleEnd).deepEquivalent())
        downstreamEnd = mostForwardCaretPosition(
            nextPositionOf(visibleEnd, CannotCrossEditingBoundary)
                .deepEquivalent());
      if (isDisplayInsideTable(downstreamEnd.computeContainerNode()) &&
          downstreamEnd.computeOffsetInContainerNode() <=
              caretMinOffset(downstreamEnd.computeContainerNode())) {
        setEndingSelection(
            SelectionInDOMTree::Builder()
                .setBaseAndExtentDeprecated(
                    endingSelection().end(),
                    Position::afterNode(downstreamEnd.computeContainerNode()))
                .setIsDirectional(endingSelection().isDirectional())
                .build());
        typingAddedToOpenCommand(ForwardDeleteKey);
        return;
      }

      if (granularity == ParagraphBoundary &&
          selectionModifier.selection().isCaret() &&
          isEndOfParagraph(selectionModifier.selection().visibleEnd()))
        selectionModifier.modify(FrameSelection::AlterationExtend,
                                 DirectionForward, CharacterGranularity);

      selectionToDelete = selectionModifier.selection();
      if (!startingSelection().isRange() ||
          selectionToDelete.base() != startingSelection().start()) {
        selectionAfterUndo = selectionToDelete;
      } else {
        Position extent = startingSelection().end();
        if (extent.computeContainerNode() !=
            selectionToDelete.end().computeContainerNode()) {
          extent = selectionToDelete.extent();
        } else {
          int extraCharacters;
          if (selectionToDelete.start().computeContainerNode() ==
              selectionToDelete.end().computeContainerNode())
            extraCharacters =
                selectionToDelete.end().computeOffsetInContainerNode() -
                selectionToDelete.start().computeOffsetInContainerNode();
          else
            extraCharacters =
                selectionToDelete.end().computeOffsetInContainerNode();
          extent =
              Position(extent.computeContainerNode(),
                       extent.computeOffsetInContainerNode() + extraCharacters);
        }
        selectionAfterUndo.setWithoutValidation(startingSelection().start(),
                                                extent);
      }
      break;
    }
    case NoSelection:
      NOTREACHED();
      break;
  }

  DCHECK(!selectionToDelete.isNone());
  if (selectionToDelete.isNone())
    return;

  if (selectionToDelete.isCaret())
    return;

  if (killRing)
    frame->editor().addToKillRing(
        selectionToDelete.toNormalizedEphemeralRange());
  if (frame->editor().behavior().shouldUndoOfDeleteSelectText())
    setStartingSelection(selectionAfterUndo);
  deleteSelectionIfRange(selectionToDelete, editingState, m_smartDelete);
  if (editingState->isAborted())
    return;
  setSmartDelete(false);
  typingAddedToOpenCommand(ForwardDeleteKey);
}
