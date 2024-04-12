Address NormalPageArena::AllocateFromFreeList(size_t allocation_size,
                                              size_t gc_info_index) {
  size_t bucket_size = static_cast<size_t>(1)
                       << free_list_.biggest_free_list_index_;
  int index = free_list_.biggest_free_list_index_;
  for (; index > 0; --index, bucket_size >>= 1) {
    FreeListEntry* entry = free_list_.free_lists_[index];
    if (allocation_size > bucket_size) {
      if (!entry || entry->size() < allocation_size)
        break;
    }
    if (entry) {
      entry->Unlink(&free_list_.free_lists_[index]);
      SetAllocationPoint(entry->GetAddress(), entry->size());
      DCHECK(HasCurrentAllocationArea());
      DCHECK_GE(RemainingAllocationSize(), allocation_size);
      free_list_.biggest_free_list_index_ = index;
      return AllocateObject(allocation_size, gc_info_index);
    }
  }
  free_list_.biggest_free_list_index_ = index;
  return nullptr;
}
