void HeapCache::dump_heaps()
{
 Mutex::Autolock _l(mHeapCacheLock);
 int c = mHeapCache.size();
 for (int i=0 ; i<c ; i++) {
 const heap_info_t& info = mHeapCache.valueAt(i);
 BpMemoryHeap const* h(static_cast<BpMemoryHeap const *>(info.heap.get()));
        ALOGD("hey=%p, heap=%p, count=%d, (fd=%d, base=%p, size=%zu)",
                mHeapCache.keyAt(i).unsafe_get(),
                info.heap.get(), info.count,
                h->mHeapId, h->mBase, h->mSize);
 }
}
