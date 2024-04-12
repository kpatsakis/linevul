InputMethodIBus::~InputMethodIBus() {
  AbandonAllPendingKeyEvents();
  DestroyContext();

  g_signal_handlers_disconnect_by_func(
      GetBus(), reinterpret_cast<gpointer>(OnIBusConnectedThunk), this);
  g_signal_handlers_disconnect_by_func(
      GetBus(), reinterpret_cast<gpointer>(OnIBusDisconnectedThunk), this);
}
