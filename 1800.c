bool MemBackendImpl::SetMaxSize(int max_bytes) {
  static_assert(sizeof(max_bytes) == sizeof(max_size_),
                "unsupported int model");
  if (max_bytes < 0)
    return false;

  if (!max_bytes)
    return true;

  max_size_ = max_bytes;
  return true;
}
