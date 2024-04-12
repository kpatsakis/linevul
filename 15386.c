void NormalPageArena::AllocatePage() {
  GetThreadState()->Heap().address_cache()->MarkDirty();
  PageMemory* page_memory =
      GetThreadState()->Heap().GetFreePagePool()->Take(ArenaIndex());

  if (!page_memory) {
    PageMemoryRegion* region = PageMemoryRegion::AllocateNormalPages(
        GetThreadState()->Heap().GetRegionTree());

    for (size_t i = 0; i < kBlinkPagesPerRegion; ++i) {
      PageMemory* memory = PageMemory::SetupPageMemoryInRegion(
          region, i * kBlinkPageSize, BlinkPagePayloadSize());
      if (!page_memory) {
        bool result = memory->Commit();
        CHECK(result);
        page_memory = memory;
      } else {
        GetThreadState()->Heap().GetFreePagePool()->Add(ArenaIndex(), memory);
      }
    }
  }
  NormalPage* page =
      new (page_memory->WritableStart()) NormalPage(page_memory, this);
  page->Link(&first_page_);

  GetThreadState()->Heap().HeapStats().IncreaseAllocatedSpace(page->size());
#if DCHECK_IS_ON() || defined(LEAK_SANITIZER) || defined(ADDRESS_SANITIZER)
  ASAN_UNPOISON_MEMORY_REGION(page->Payload(), page->PayloadSize());
  Address address = page->Payload();
  for (size_t i = 0; i < page->PayloadSize(); i++)
    address[i] = kReuseAllowedZapValue;
  ASAN_POISON_MEMORY_REGION(page->Payload(), page->PayloadSize());
#endif
  AddToFreeList(page->Payload(), page->PayloadSize());
}
