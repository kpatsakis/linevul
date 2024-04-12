void NormalPageArena::VerifyMarking() {
#if DCHECK_IS_ON()
  SetAllocationPoint(nullptr, 0);
  for (NormalPage* page = static_cast<NormalPage*>(first_page_); page;
       page = static_cast<NormalPage*>(page->Next()))
    page->VerifyMarking();
#endif  // DCHECK_IS_ON()
}
