scoped_refptr<PrintBackend> PrintBackend::CreateInstance(
    const base::DictionaryValue* print_backend_settings) {
  return new PrintBackendWin;
}
