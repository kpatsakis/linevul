DictionaryValue* SessionHeaderToValue(
    const sync_pb::SessionHeader& proto) {
  DictionaryValue* value = new DictionaryValue();
  SET_REP(window, SessionWindowToValue);
  SET_STR(client_name);
  SET_ENUM(device_type, GetDeviceTypeString);
  return value;
}
