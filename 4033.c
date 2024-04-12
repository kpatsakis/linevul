static struct sit_entry_set *grab_sit_entry_set(void)
{
	struct sit_entry_set *ses =
			f2fs_kmem_cache_alloc(sit_entry_set_slab, GFP_NOFS);

	ses->entry_cnt = 0;
	INIT_LIST_HEAD(&ses->set_list);
	return ses;
}
