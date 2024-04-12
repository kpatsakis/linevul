IBusBus* InputMethodIBus::GetBus() {
  static IBusBus* ibus = NULL;

  if (!ibus) {
    ibus = ibus_client_->GetConnection();
    DCHECK(ibus);
  }
  return ibus;
}
