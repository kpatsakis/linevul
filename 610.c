void* AsyncId(unsigned long identifier) {
  return reinterpret_cast<void*>((identifier << 1) | 1);
}
