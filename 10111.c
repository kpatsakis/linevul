void ChromotingInstance::HandleTrapKey(const base::DictionaryValue& data) {
  int keycode = 0;
  bool trap = false;
  if (!data.GetInteger("keycode", &keycode) ||
      !data.GetBoolean("trap", &trap)) {
    LOG(ERROR) << "Invalid trapKey.";
    return;
  }

  key_mapper_.TrapKey(keycode, trap);
}
