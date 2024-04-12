void Bluetooth::ContextDestroyed(ExecutionContext*) {
  client_bindings_.CloseAllBindings();
}
