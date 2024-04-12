void LocalFrame::RemoveSpellingMarkersUnderWords(const Vector<String>& words) {
  GetSpellChecker().RemoveSpellingMarkersUnderWords(words);
}
