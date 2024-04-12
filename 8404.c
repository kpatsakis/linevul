void TypingCommand::insertTextRunWithoutNewlines(const String& text,
                                                 bool selectInsertedText,
                                                 EditingState* editingState) {
  CompositeEditCommand* command;
  if (isIncrementalInsertion()) {
    command = InsertIncrementalTextCommand::create(
        document(), text, selectInsertedText,
        m_compositionType == TextCompositionNone
            ? InsertIncrementalTextCommand::
                  RebalanceLeadingAndTrailingWhitespaces
            : InsertIncrementalTextCommand::RebalanceAllWhitespaces);
  } else {
    command = InsertTextCommand::create(
        document(), text, selectInsertedText,
        m_compositionType == TextCompositionNone
            ? InsertTextCommand::RebalanceLeadingAndTrailingWhitespaces
            : InsertTextCommand::RebalanceAllWhitespaces);
  }

  applyCommandToComposite(command, endingSelection(), editingState);
  if (editingState->isAborted())
    return;

  typingAddedToOpenCommand(InsertText);
}
