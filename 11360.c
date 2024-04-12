bool ValidityMessages::HasErrors() const {
  for (MessageMap::const_iterator iter = messages_.begin();
       iter != messages_.end(); ++iter) {
    if (!iter->second.text.empty())
      return true;
  }
  return false;
}
