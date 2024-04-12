int sync_node_pages(struct f2fs_sb_info *sbi, struct writeback_control *wbc)
{
	pgoff_t index, end;
	struct pagevec pvec;
	int step = 0;
	int nwritten = 0;
	int ret = 0;

	pagevec_init(&pvec, 0);

next_step:
	index = 0;
	end = ULONG_MAX;

	while (index <= end) {
		int i, nr_pages;
		nr_pages = pagevec_lookup_tag(&pvec, NODE_MAPPING(sbi), &index,
				PAGECACHE_TAG_DIRTY,
				min(end - index, (pgoff_t)PAGEVEC_SIZE-1) + 1);
		if (nr_pages == 0)
			break;

		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];
			bool submitted = false;

			if (unlikely(f2fs_cp_error(sbi))) {
				pagevec_release(&pvec);
				ret = -EIO;
				goto out;
			}

			/*
			 * flushing sequence with step:
			 * 0. indirect nodes
			 * 1. dentry dnodes
			 * 2. file dnodes
			 */
			if (step == 0 && IS_DNODE(page))
				continue;
			if (step == 1 && (!IS_DNODE(page) ||
						is_cold_node(page)))
				continue;
			if (step == 2 && (!IS_DNODE(page) ||
						!is_cold_node(page)))
				continue;
lock_node:
			if (!trylock_page(page))
				continue;

			if (unlikely(page->mapping != NODE_MAPPING(sbi))) {
continue_unlock:
				unlock_page(page);
				continue;
			}

			if (!PageDirty(page)) {
				/* someone wrote it for us */
				goto continue_unlock;
			}

			/* flush inline_data */
			if (is_inline_node(page)) {
				clear_inline_node(page);
				unlock_page(page);
				flush_inline_data(sbi, ino_of_node(page));
				goto lock_node;
			}

			f2fs_wait_on_page_writeback(page, NODE, true);

			BUG_ON(PageWriteback(page));
			if (!clear_page_dirty_for_io(page))
				goto continue_unlock;

			set_fsync_mark(page, 0);
			set_dentry_mark(page, 0);

			ret = __write_node_page(page, false, &submitted, wbc);
			if (ret)
				unlock_page(page);
			else if (submitted)
				nwritten++;

			if (--wbc->nr_to_write == 0)
				break;
		}
		pagevec_release(&pvec);
		cond_resched();

		if (wbc->nr_to_write == 0) {
			step = 2;
			break;
		}
	}

	if (step < 2) {
		step++;
		goto next_step;
	}
out:
	if (nwritten)
		f2fs_submit_merged_bio(sbi, NODE, WRITE);
	return ret;
}
