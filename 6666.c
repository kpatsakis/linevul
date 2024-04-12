DictionaryValue* GetSettingsDictionary(const ListValue* args) {
  std::string json_str;
  if (!args->GetString(0, &json_str)) {
    NOTREACHED() << "Could not read JSON argument";
    return NULL;
  }
  if (json_str.empty()) {
    NOTREACHED() << "Empty print job settings";
    return NULL;
  }
  scoped_ptr<DictionaryValue> settings(static_cast<DictionaryValue*>(
      base::JSONReader::Read(json_str)));
  if (!settings.get() || !settings->IsType(Value::TYPE_DICTIONARY)) {
    NOTREACHED() << "Print job settings must be a dictionary.";
    return NULL;
  }

  if (settings->empty()) {
    NOTREACHED() << "Print job settings dictionary is empty";
    return NULL;
  }

  return settings.release();
}
