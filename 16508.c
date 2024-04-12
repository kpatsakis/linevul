DictionaryValue* ExtensionPrefs::CopyCurrentExtensions() {
  const DictionaryValue* extensions = prefs_->GetDictionary(kExtensionsPref);
  if (extensions) {
    DictionaryValue* copy = extensions->DeepCopy();
    MakePathsAbsolute(copy);
    return copy;
  }
  return new DictionaryValue;
}
