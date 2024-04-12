void LargeObjectArena::freeLargeObjectPage(LargeObjectPage* object) {
  ASAN_UNPOISON_MEMORY_REGION(object->payload(), object->payloadSize());
  object->heapObjectHeader()->finalize(object->payload(),
                                       object->payloadSize());
  getThreadState()->heap().heapStats().decreaseAllocatedSpace(object->size());

  ASAN_UNPOISON_MEMORY_REGION(object->heapObjectHeader(),
                              sizeof(HeapObjectHeader));
  ASAN_UNPOISON_MEMORY_REGION(object->getAddress() + object->size(),
                              allocationGranularity);

  PageMemory* memory = object->storage();
  object->~LargeObjectPage();
  delete memory;
}
