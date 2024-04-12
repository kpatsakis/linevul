DictionaryValue* ChromiumExtensionActivityToValue(
    const sync_pb::ChromiumExtensionsActivity& proto) {
  DictionaryValue* value = new DictionaryValue();
  SET_STR(extension_id);
  SET_INT32(bookmark_writes_since_last_commit);
  return value;
}
