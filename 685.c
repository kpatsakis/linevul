void NEVER_INLINE FreeList::checkFreedMemoryIsZapped(Address address,
                                                     size_t size) {
  for (size_t i = 0; i < size; i++) {
    ASSERT(address[i] == reuseAllowedZapValue ||
           address[i] == reuseForbiddenZapValue);
  }
}
