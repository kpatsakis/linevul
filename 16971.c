bool Extension::IdIsValid(const std::string& id) {
  if (id.size() != (kIdSize * 2))
    return false;

  std::string temp = StringToLowerASCII(id);
  for (size_t i = 0; i < temp.size(); i++)
    if (temp[i] < 'a' || temp[i] > 'p')
      return false;

  return true;
}
