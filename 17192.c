static void __init khugepaged_slab_free(void)
{
	kmem_cache_destroy(mm_slot_cache);
	mm_slot_cache = NULL;
}
