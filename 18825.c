static bool IsKeyValueInDict(const JsonKeyValue* key_value,
                             DictionaryValue* dict) {
  Value* value = NULL;
  std::string value_str;
  if (dict->Get(key_value->key, &value) &&
      value->GetAsString(&value_str) &&
      CompareJsonValues(value_str, key_value->value, key_value->op))
    return true;

  DictionaryValue* args_dict = NULL;
  dict->GetDictionary("args", &args_dict);
  if (args_dict)
    return IsKeyValueInDict(key_value, args_dict);

  return false;
}
