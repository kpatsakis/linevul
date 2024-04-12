Address LargeObjectArena::LazySweepPages(size_t allocation_size,
                                         size_t gc_info_index) {
  Address result = nullptr;
  size_t swept_size = 0;
  while (!SweepingCompleted()) {
    BasePage* page = first_unswept_page_;
    if (page->IsEmpty()) {
      swept_size += static_cast<LargeObjectPage*>(page)->PayloadSize();
      page->Unlink(&first_unswept_page_);
      page->RemoveFromHeap();
      if (swept_size >= allocation_size) {
        result = DoAllocateLargeObjectPage(allocation_size, gc_info_index);
        DCHECK(result);
        break;
      }
    } else {
      page->Sweep();
      page->Unlink(&first_unswept_page_);
      page->Link(&first_page_);
      page->MarkAsSwept();
    }
  }
  return result;
}
