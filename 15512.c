DictionaryValue* AppSpecificsToValue(
    const sync_pb::AppSpecifics& proto) {
  DictionaryValue* value = new DictionaryValue();
  SET(extension, ExtensionSpecificsToValue);
  SET(notification_settings, AppSettingsToValue);
  SET_STR(app_launch_ordinal);
  SET_STR(page_ordinal);

  return value;
}
