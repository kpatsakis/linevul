TypingCommand::TypingCommand(Document& document,
                             ETypingCommand commandType,
                             const String& textToInsert,
                             Options options,
                             TextGranularity granularity,
                             TextCompositionType compositionType)
    : CompositeEditCommand(document),
      m_commandType(commandType),
      m_textToInsert(textToInsert),
      m_openForMoreTyping(true),
      m_selectInsertedText(options & SelectInsertedText),
      m_smartDelete(options & SmartDelete),
      m_granularity(granularity),
      m_compositionType(compositionType),
      m_killRing(options & KillRing),
      m_openedByBackwardDelete(false),
      m_shouldRetainAutocorrectionIndicator(options &
                                            RetainAutocorrectionIndicator),
      m_shouldPreventSpellChecking(options & PreventSpellChecking) {
  updatePreservesTypingStyle(m_commandType);
}
