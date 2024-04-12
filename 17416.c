sp<IMemoryHeap> HeapCache::get_heap(const sp<IBinder>& binder)
{
    sp<IMemoryHeap> realHeap;
 Mutex::Autolock _l(mHeapCacheLock);
 ssize_t i = mHeapCache.indexOfKey(binder);
 if (i>=0)   realHeap = mHeapCache.valueAt(i).heap;
 else        realHeap = interface_cast<IMemoryHeap>(binder);
 return realHeap;
}
