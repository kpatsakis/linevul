ListValue* MakeRepeatedValue(const F& fields, V* (*converter_fn)(T)) {
  ListValue* list = new ListValue();
  for (typename F::const_iterator it = fields.begin(); it != fields.end();
       ++it) {
    list->Append(converter_fn(*it));
  }
  return list;
}
