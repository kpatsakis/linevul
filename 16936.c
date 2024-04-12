std::vector<const DictionaryValue*> FindTraceEntries(
    const ListValue& trace_parsed,
    const char* string_to_match) {
  std::vector<const DictionaryValue*> hits;
  size_t trace_parsed_count = trace_parsed.GetSize();
  for (size_t i = 0; i < trace_parsed_count; i++) {
    const Value* value = NULL;
    trace_parsed.Get(i, &value);
    if (!value || value->GetType() != Value::TYPE_DICTIONARY)
      continue;
    const DictionaryValue* dict = static_cast<const DictionaryValue*>(value);

    if (IsStringInDict(string_to_match, dict))
      hits.push_back(dict);
  }
  return hits;
}
