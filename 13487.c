Address LargeObjectArena::lazySweepPages(size_t allocationSize,
                                         size_t gcInfoIndex) {
  Address result = nullptr;
  size_t sweptSize = 0;
  while (m_firstUnsweptPage) {
    BasePage* page = m_firstUnsweptPage;
    if (page->isEmpty()) {
      sweptSize += static_cast<LargeObjectPage*>(page)->payloadSize() +
                   sizeof(HeapObjectHeader);
      page->unlink(&m_firstUnsweptPage);
      page->removeFromHeap();
      if (sweptSize >= allocationSize) {
        result = doAllocateLargeObjectPage(allocationSize, gcInfoIndex);
        ASSERT(result);
        break;
      }
    } else {
      page->sweep();
      page->unlink(&m_firstUnsweptPage);
      page->link(&m_firstPage);
      page->markAsSwept();
    }
  }
  return result;
}
