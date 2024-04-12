static bool IsAllKeyValueInDict(const JsonKeyValue* key_values,
                                DictionaryValue* dict) {
  while (key_values && key_values->key) {
    if (!IsKeyValueInDict(key_values, dict))
      return false;
    ++key_values;
  }
  return true;
}
