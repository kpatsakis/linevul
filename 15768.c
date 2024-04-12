void TraceEventTestFixture::DropTracedMetadataRecords() {
  scoped_ptr<ListValue> old_trace_parsed(trace_parsed_.DeepCopy());
  size_t old_trace_parsed_size = old_trace_parsed->GetSize();
  trace_parsed_.Clear();

  for (size_t i = 0; i < old_trace_parsed_size; i++) {
    Value* value = NULL;
    old_trace_parsed->Get(i, &value);
    if (!value || value->GetType() != Value::TYPE_DICTIONARY) {
      trace_parsed_.Append(value->DeepCopy());
      continue;
    }
    DictionaryValue* dict = static_cast<DictionaryValue*>(value);
    std::string tmp;
    if (dict->GetString("ph", &tmp) && tmp == "M")
      continue;

    trace_parsed_.Append(value->DeepCopy());
  }
}
