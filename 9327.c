ClientSharedBitmapManager::GetBitmapForSharedMemory(base::SharedMemory* mem) {
  SharedBitmapId id = SharedBitmap::GenerateId();
  uint32_t sequence_number = NotifyAllocatedSharedBitmap(mem, id);
  return std::make_unique<ClientSharedBitmap>(
      shared_bitmap_allocation_notifier_, mem, id, sequence_number);
}
