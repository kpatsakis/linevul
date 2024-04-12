void TypingCommand::updatePreservesTypingStyle(ETypingCommand commandType) {
  switch (commandType) {
    case DeleteSelection:
    case DeleteKey:
    case ForwardDeleteKey:
    case InsertParagraphSeparator:
    case InsertLineBreak:
      m_preservesTypingStyle = true;
      return;
    case InsertParagraphSeparatorInQuotedContent:
    case InsertText:
      m_preservesTypingStyle = false;
      return;
  }
  NOTREACHED();
  m_preservesTypingStyle = false;
}
