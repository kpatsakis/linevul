void HeapCache::free_heap(const wp<IBinder>& binder)
{
    sp<IMemoryHeap> rel;
 {
 Mutex::Autolock _l(mHeapCacheLock);
 ssize_t i = mHeapCache.indexOfKey(binder);
 if (i>=0) {
 heap_info_t& info(mHeapCache.editValueAt(i));
 int32_t c = android_atomic_dec(&info.count);
 if (c == 1) {
                ALOGD_IF(VERBOSE,
 "removing binder=%p, heap=%p, size=%zu, fd=%d, count=%d",
                        binder.unsafe_get(), info.heap.get(),
 static_cast<BpMemoryHeap*>(info.heap.get())->mSize,
 static_cast<BpMemoryHeap*>(info.heap.get())->mHeapId,
                        info.count);
                rel = mHeapCache.valueAt(i).heap;
                mHeapCache.removeItemsAt(i);
 }
 } else {
            ALOGE("free_heap binder=%p not found!!!", binder.unsafe_get());
 }
 }
}
