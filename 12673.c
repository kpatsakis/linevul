void ext4_da_update_reserve_space(struct inode *inode,
					int used, int quota_claim)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_inode_info *ei = EXT4_I(inode);
	int mdb_free = 0, allocated_meta_blocks = 0;

	spin_lock(&ei->i_block_reservation_lock);
	trace_ext4_da_update_reserve_space(inode, used);
	if (unlikely(used > ei->i_reserved_data_blocks)) {
		ext4_msg(inode->i_sb, KERN_NOTICE, "%s: ino %lu, used %d "
			 "with only %d reserved data blocks\n",
			 __func__, inode->i_ino, used,
			 ei->i_reserved_data_blocks);
		WARN_ON(1);
		used = ei->i_reserved_data_blocks;
	}

	/* Update per-inode reservations */
	ei->i_reserved_data_blocks -= used;
	used += ei->i_allocated_meta_blocks;
	ei->i_reserved_meta_blocks -= ei->i_allocated_meta_blocks;
	allocated_meta_blocks = ei->i_allocated_meta_blocks;
	ei->i_allocated_meta_blocks = 0;
	percpu_counter_sub(&sbi->s_dirtyblocks_counter, used);

	if (ei->i_reserved_data_blocks == 0) {
		/*
		 * We can release all of the reserved metadata blocks
		 * only when we have written all of the delayed
		 * allocation blocks.
		 */
		mdb_free = ei->i_reserved_meta_blocks;
		ei->i_reserved_meta_blocks = 0;
		ei->i_da_metadata_calc_len = 0;
		percpu_counter_sub(&sbi->s_dirtyblocks_counter, mdb_free);
	}
	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);

	/* Update quota subsystem */
	if (quota_claim) {
		vfs_dq_claim_block(inode, used);
		if (mdb_free)
			vfs_dq_release_reservation_block(inode, mdb_free);
	} else {
		/*
		 * We did fallocate with an offset that is already delayed
		 * allocated. So on delayed allocated writeback we should
		 * not update the quota for allocated blocks. But then
		 * converting an fallocate region to initialized region would
		 * have caused a metadata allocation. So claim quota for
		 * that
		 */
		if (allocated_meta_blocks)
			vfs_dq_claim_block(inode, allocated_meta_blocks);
		vfs_dq_release_reservation_block(inode, mdb_free + used);
	}

	/*
	 * If we have done all the pending block allocations and if
	 * there aren't any writers on the inode, we can discard the
	 * inode's preallocations.
	 */
	if ((ei->i_reserved_data_blocks == 0) &&
	    (atomic_read(&inode->i_writecount) == 0))
		ext4_discard_preallocations(inode);
}
