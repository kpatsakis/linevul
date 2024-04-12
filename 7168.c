void ChromotingInstance::HandleRemapKey(const base::DictionaryValue& data) {
  int from_keycode = 0;
  int to_keycode = 0;
  if (!data.GetInteger("fromKeycode", &from_keycode) ||
      !data.GetInteger("toKeycode", &to_keycode)) {
    LOG(ERROR) << "Invalid remapKey.";
    return;
  }

  key_mapper_.RemapKey(from_keycode, to_keycode);
}
