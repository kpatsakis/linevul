bool RenderProcessImpl::GetTransportDIBFromCache(TransportDIB** mem,
                                             size_t size) {
  for (size_t i = 0; i < arraysize(shared_mem_cache_); ++i) {
    if (shared_mem_cache_[i] &&
        size <= shared_mem_cache_[i]->size()) {
      *mem = shared_mem_cache_[i];
      shared_mem_cache_[i] = NULL;
      return true;
    }
  }

  return false;
}
