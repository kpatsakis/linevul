bool Editor::isSelectTrailingWhitespaceEnabled() const {
  if (Settings* settings = frame().settings())
    return settings->getSelectTrailingWhitespaceEnabled();
  return false;
}
