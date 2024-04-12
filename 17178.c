void Editor::toggleOverwriteModeEnabled() {
  m_overwriteModeEnabled = !m_overwriteModeEnabled;
  frame().selection().setShouldShowBlockCursor(m_overwriteModeEnabled);
}
