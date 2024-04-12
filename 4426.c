bool BluetoothRemoteGATTServer::RemoveFromActiveAlgorithms(
    ScriptPromiseResolver* resolver) {
  if (!m_activeAlgorithms.contains(resolver)) {
    return false;
  }
  m_activeAlgorithms.remove(resolver);
  return true;
}
