static int ext4_meta_trans_blocks(struct inode *inode, int lblocks,
				  int pextents)
{
	ext4_group_t groups, ngroups = ext4_get_groups_count(inode->i_sb);
	int gdpblocks;
	int idxblocks;
	int ret = 0;

	/*
	 * How many index blocks need to touch to map @lblocks logical blocks
	 * to @pextents physical extents?
	 */
	idxblocks = ext4_index_trans_blocks(inode, lblocks, pextents);

	ret = idxblocks;

	/*
	 * Now let's see how many group bitmaps and group descriptors need
	 * to account
	 */
	groups = idxblocks + pextents;
	gdpblocks = groups;
	if (groups > ngroups)
		groups = ngroups;
	if (groups > EXT4_SB(inode->i_sb)->s_gdb_count)
		gdpblocks = EXT4_SB(inode->i_sb)->s_gdb_count;

	/* bitmaps and block group descriptor blocks */
	ret += groups + gdpblocks;

	/* Blocks for super block, inode, quota and xattr blocks */
	ret += EXT4_META_TRANS_BLOCKS(inode->i_sb);

	return ret;
}
