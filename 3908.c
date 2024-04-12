DEFINE_TRACE(BluetoothRemoteGATTServer) {
  visitor->trace(m_activeAlgorithms);
  visitor->trace(m_device);
}
