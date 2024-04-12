void SetExplicitlyAllowedPorts(const std::string& allowed_ports) {
  if (allowed_ports.empty())
    return;

  std::multiset<int> ports;
  size_t last = 0;
  size_t size = allowed_ports.size();
  const std::string::value_type kComma = ',';

  for (size_t i = 0; i <= size; ++i) {
    if (i != size && !base::IsAsciiDigit(allowed_ports[i]) &&
        (allowed_ports[i] != kComma))
      return;
    if (i == size || allowed_ports[i] == kComma) {
      if (i > last) {
        int port;
        base::StringToInt(base::StringPiece(allowed_ports.begin() + last,
                                            allowed_ports.begin() + i),
                          &port);
        ports.insert(port);
      }
      last = i + 1;
    }
  }
  g_explicitly_allowed_ports.Get() = ports;
}
