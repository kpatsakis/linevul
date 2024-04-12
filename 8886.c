bool ExtensionPrefs::GetActiveBit(const std::string& extension_id) {
  const DictionaryValue* dictionary = GetExtensionPref(extension_id);
  bool result = false;
  if (dictionary && dictionary->GetBoolean(kActiveBit, &result))
    return result;
  return false;
}
