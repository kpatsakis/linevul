void GetPrinterHelper(HANDLE printer, int level, scoped_array<uint8>* buffer) {
  DWORD buf_size = 0;
  GetPrinter(printer, level, NULL, 0, &buf_size);
  if (buf_size) {
    buffer->reset(new uint8[buf_size]);
    memset(buffer->get(), 0, buf_size);
    if (!GetPrinter(printer, level, buffer->get(), buf_size, &buf_size)) {
      buffer->reset();
    }
  }
}
