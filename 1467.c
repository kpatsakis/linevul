int DiskCacheBackendTest::GetRoundedSize(int exact_size) {
  if (!simple_cache_mode_)
    return exact_size;

  return (exact_size + 255) & 0xFFFFFF00;
}
