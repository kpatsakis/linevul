int FreeList::bucketIndexForSize(size_t size) {
  ASSERT(size > 0);
  int index = -1;
  while (size) {
    size >>= 1;
    index++;
  }
  return index;
}
