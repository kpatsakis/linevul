void NormalPageArena::TakeFreelistSnapshot(const String& dump_name) {
  if (free_list_.TakeSnapshot(dump_name)) {
    base::trace_event::MemoryAllocatorDump* buckets_dump =
        BlinkGCMemoryDumpProvider::Instance()
            ->CreateMemoryAllocatorDumpForCurrentGC(dump_name + "/buckets");
    base::trace_event::MemoryAllocatorDump* pages_dump =
        BlinkGCMemoryDumpProvider::Instance()
            ->CreateMemoryAllocatorDumpForCurrentGC(dump_name + "/pages");
    BlinkGCMemoryDumpProvider::Instance()
        ->CurrentProcessMemoryDump()
        ->AddOwnershipEdge(pages_dump->guid(), buckets_dump->guid());
  }
}
