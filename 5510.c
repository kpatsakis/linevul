int read_super(char *source)
{
	squashfs_super_block_3 sBlk_3;
	struct squashfs_super_block sBlk_4;

	/*
	 * Try to read a Squashfs 4 superblock
	 */
	read_fs_bytes(fd, SQUASHFS_START, sizeof(struct squashfs_super_block),
		&sBlk_4);
	swap = sBlk_4.s_magic != SQUASHFS_MAGIC;
	SQUASHFS_INSWAP_SUPER_BLOCK(&sBlk_4);

	if(sBlk_4.s_magic == SQUASHFS_MAGIC && sBlk_4.s_major == 4 &&
			sBlk_4.s_minor == 0) {
		s_ops.read_filesystem_tables = read_filesystem_tables_4;
		s_ops.squashfs_opendir = squashfs_opendir_4;
		s_ops.read_fragment = read_fragment_4;
		s_ops.read_block_list = read_block_list_2;
		s_ops.read_inode = read_inode_4;
		memcpy(&sBlk, &sBlk_4, sizeof(sBlk_4));

		/*
		 * Check the compression type
		 */
		comp = lookup_compressor_id(sBlk.s.compression);
		return TRUE;
	}

	/*
 	 * Not a Squashfs 4 superblock, try to read a squashfs 3 superblock
 	 * (compatible with 1 and 2 filesystems)
 	 */
	read_fs_bytes(fd, SQUASHFS_START, sizeof(squashfs_super_block_3),
		&sBlk_3);

	/*
	 * Check it is a SQUASHFS superblock
	 */
	swap = 0;
	if(sBlk_3.s_magic != SQUASHFS_MAGIC) {
		if(sBlk_3.s_magic == SQUASHFS_MAGIC_SWAP) {
			squashfs_super_block_3 sblk;
			ERROR("Reading a different endian SQUASHFS filesystem "
				"on %s\n", source);
			SQUASHFS_SWAP_SUPER_BLOCK_3(&sblk, &sBlk_3);
			memcpy(&sBlk_3, &sblk, sizeof(squashfs_super_block_3));
			swap = 1;
		} else  {
			ERROR("Can't find a SQUASHFS superblock on %s\n",
				source);
			goto failed_mount;
		}
	}

	sBlk.s.s_magic = sBlk_3.s_magic;
	sBlk.s.inodes = sBlk_3.inodes;
	sBlk.s.mkfs_time = sBlk_3.mkfs_time;
	sBlk.s.block_size = sBlk_3.block_size;
	sBlk.s.fragments = sBlk_3.fragments;
	sBlk.s.block_log = sBlk_3.block_log;
	sBlk.s.flags = sBlk_3.flags;
	sBlk.s.s_major = sBlk_3.s_major;
	sBlk.s.s_minor = sBlk_3.s_minor;
	sBlk.s.root_inode = sBlk_3.root_inode;
	sBlk.s.bytes_used = sBlk_3.bytes_used;
	sBlk.s.inode_table_start = sBlk_3.inode_table_start;
	sBlk.s.directory_table_start = sBlk_3.directory_table_start;
	sBlk.s.fragment_table_start = sBlk_3.fragment_table_start;
	sBlk.s.lookup_table_start = sBlk_3.lookup_table_start;
	sBlk.no_uids = sBlk_3.no_uids;
	sBlk.no_guids = sBlk_3.no_guids;
	sBlk.uid_start = sBlk_3.uid_start;
	sBlk.guid_start = sBlk_3.guid_start;
	sBlk.s.xattr_id_table_start = SQUASHFS_INVALID_BLK;

	/* Check the MAJOR & MINOR versions */
	if(sBlk.s.s_major == 1 || sBlk.s.s_major == 2) {
		sBlk.s.bytes_used = sBlk_3.bytes_used_2;
		sBlk.uid_start = sBlk_3.uid_start_2;
		sBlk.guid_start = sBlk_3.guid_start_2;
		sBlk.s.inode_table_start = sBlk_3.inode_table_start_2;
		sBlk.s.directory_table_start = sBlk_3.directory_table_start_2;
		
		if(sBlk.s.s_major == 1) {
			sBlk.s.block_size = sBlk_3.block_size_1;
			sBlk.s.fragment_table_start = sBlk.uid_start;
			s_ops.read_filesystem_tables = read_filesystem_tables_1;
			s_ops.squashfs_opendir = squashfs_opendir_1;
			s_ops.read_block_list = read_block_list_1;
			s_ops.read_inode = read_inode_1;
		} else {
			sBlk.s.fragment_table_start =
				sBlk_3.fragment_table_start_2;
			s_ops.read_filesystem_tables = read_filesystem_tables_2;
			s_ops.squashfs_opendir = squashfs_opendir_1;
			s_ops.read_fragment = read_fragment_2;
			s_ops.read_block_list = read_block_list_2;
			s_ops.read_inode = read_inode_2;
		}
	} else if(sBlk.s.s_major == 3) {
		s_ops.read_filesystem_tables = read_filesystem_tables_3;
		s_ops.squashfs_opendir = squashfs_opendir_3;
		s_ops.read_fragment = read_fragment_3;
		s_ops.read_block_list = read_block_list_2;
		s_ops.read_inode = read_inode_3;
	} else {
		ERROR("Filesystem on %s is (%d:%d), ", source, sBlk.s.s_major,
			sBlk.s.s_minor);
		ERROR("which is a later filesystem version than I support!\n");
		goto failed_mount;
	}

	/*
	 * 1.x, 2.x and 3.x filesystems use gzip compression.
	 */
	comp = lookup_compressor("gzip");
	return TRUE;

failed_mount:
	return FALSE;
}
