void TypingCommand::insertLineBreak(EditingState* editingState) {
  if (!canAppendNewLineFeedToSelection(endingSelection()))
    return;

  applyCommandToComposite(InsertLineBreakCommand::create(document()),
                          editingState);
  if (editingState->isAborted())
    return;
  typingAddedToOpenCommand(InsertLineBreak);
}
