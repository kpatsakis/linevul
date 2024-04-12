const AtomicString& Document::RequiredCSP() {
  return Loader() ? Loader()->RequiredCSP() : g_null_atom;
}
