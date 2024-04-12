DictionaryValue* TraceEventTestFixture::FindMatchingTraceEntry(
    const JsonKeyValue* key_values) {
  size_t trace_parsed_count = trace_parsed_.GetSize();
  for (size_t i = 0; i < trace_parsed_count; i++) {
    Value* value = NULL;
    trace_parsed_.Get(i, &value);
    if (!value || value->GetType() != Value::TYPE_DICTIONARY)
      continue;
    DictionaryValue* dict = static_cast<DictionaryValue*>(value);

    if (IsAllKeyValueInDict(key_values, dict))
      return dict;
  }
  return NULL;
}
