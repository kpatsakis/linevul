static bool IsValidMIMEType(const String& type) {
  size_t slash_position = type.find('/');
  if (slash_position == kNotFound || !slash_position ||
      slash_position == type.length() - 1)
    return false;
  for (size_t i = 0; i < type.length(); ++i) {
    if (!IsRFC2616TokenCharacter(type[i]) && i != slash_position)
      return false;
  }
  return true;
}
