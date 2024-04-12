bool CanonicalizePort(const base::char16* spec,
                      const Component& port,
                      int default_port_for_scheme,
                      CanonOutput* output,
                      Component* out_port) {
  return DoPort<base::char16, base::char16>(spec, port, default_port_for_scheme,
                                            output, out_port);
}
