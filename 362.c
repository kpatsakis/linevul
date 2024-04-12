void GlobalHistogramAllocator::DeletePersistentLocation() {
  memory_allocator()->SetMemoryState(PersistentMemoryAllocator::MEMORY_DELETED);

#if defined(OS_NACL)
  NOTREACHED();
#else
  if (persistent_location_.empty())
    return;

  File file(persistent_location_,
            File::FLAG_OPEN | File::FLAG_READ | File::FLAG_DELETE_ON_CLOSE);
#endif
}
