static int gfs2_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vma->vm_file);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_alloc_parms ap = { .aflags = 0, };
	unsigned long last_index;
	u64 pos = page->index << PAGE_CACHE_SHIFT;
	unsigned int data_blocks, ind_blocks, rblocks;
	struct gfs2_holder gh;
	loff_t size;
	int ret;

	sb_start_pagefault(inode->i_sb);

	/* Update file times before taking page lock */
	file_update_time(vma->vm_file);

	ret = get_write_access(inode);
	if (ret)
		goto out;

	ret = gfs2_rs_alloc(ip);
	if (ret)
		goto out_write_access;

	gfs2_size_hint(vma->vm_file, pos, PAGE_CACHE_SIZE);

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	if (ret)
		goto out_uninit;

	set_bit(GLF_DIRTY, &ip->i_gl->gl_flags);
	set_bit(GIF_SW_PAGED, &ip->i_flags);

	if (!gfs2_write_alloc_required(ip, pos, PAGE_CACHE_SIZE)) {
		lock_page(page);
		if (!PageUptodate(page) || page->mapping != inode->i_mapping) {
			ret = -EAGAIN;
			unlock_page(page);
		}
		goto out_unlock;
	}

	ret = gfs2_rindex_update(sdp);
	if (ret)
		goto out_unlock;

	ret = gfs2_quota_lock_check(ip);
	if (ret)
		goto out_unlock;
	gfs2_write_calc_reserv(ip, PAGE_CACHE_SIZE, &data_blocks, &ind_blocks);
	ap.target = data_blocks + ind_blocks;
	ret = gfs2_inplace_reserve(ip, &ap);
	if (ret)
		goto out_quota_unlock;

	rblocks = RES_DINODE + ind_blocks;
	if (gfs2_is_jdata(ip))
		rblocks += data_blocks ? data_blocks : 1;
	if (ind_blocks || data_blocks) {
		rblocks += RES_STATFS + RES_QUOTA;
		rblocks += gfs2_rg_blocks(ip, data_blocks + ind_blocks);
	}
	ret = gfs2_trans_begin(sdp, rblocks, 0);
	if (ret)
		goto out_trans_fail;

	lock_page(page);
	ret = -EINVAL;
	size = i_size_read(inode);
	last_index = (size - 1) >> PAGE_CACHE_SHIFT;
	/* Check page index against inode size */
	if (size == 0 || (page->index > last_index))
		goto out_trans_end;

	ret = -EAGAIN;
	/* If truncated, we must retry the operation, we may have raced
	 * with the glock demotion code.
	 */
	if (!PageUptodate(page) || page->mapping != inode->i_mapping)
		goto out_trans_end;

	/* Unstuff, if required, and allocate backing blocks for page */
	ret = 0;
	if (gfs2_is_stuffed(ip))
		ret = gfs2_unstuff_dinode(ip, page);
	if (ret == 0)
		ret = gfs2_allocate_page_backing(page);

out_trans_end:
	if (ret)
		unlock_page(page);
	gfs2_trans_end(sdp);
out_trans_fail:
	gfs2_inplace_release(ip);
out_quota_unlock:
	gfs2_quota_unlock(ip);
out_unlock:
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	if (ret == 0) {
		set_page_dirty(page);
		wait_for_stable_page(page);
	}
out_write_access:
	put_write_access(inode);
out:
	sb_end_pagefault(inode->i_sb);
	return block_page_mkwrite_return(ret);
}
