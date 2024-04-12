Value* ChromeNetworkDelegate::SessionNetworkStatsInfoToValue() const {
  DictionaryValue* dict = new DictionaryValue();
  dict->SetString("session_received_content_length",
                  base::Int64ToString(received_content_length_));
  dict->SetString("session_original_content_length",
                  base::Int64ToString(original_content_length_));
  return dict;
}
