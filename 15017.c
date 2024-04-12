FcDirCacheDisposeUnlocked (FcCache *cache)
{
    FcCacheRemoveUnlocked (cache);

    switch (cache->magic) {
    case FC_CACHE_MAGIC_ALLOC:
	free (cache);
	break;
    case FC_CACHE_MAGIC_MMAP:
#if defined(HAVE_MMAP) || defined(__CYGWIN__)
	munmap (cache, cache->size);
#elif defined(_WIN32)
	UnmapViewOfFile (cache);
#endif
	break;
    }
}
