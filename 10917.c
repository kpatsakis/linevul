static Value* CreateDebuggeeId(int tab_id) {
  DictionaryValue* debuggeeId = new DictionaryValue();
  debuggeeId->SetInteger(keys::kTabIdKey, tab_id);
  return debuggeeId;
}
