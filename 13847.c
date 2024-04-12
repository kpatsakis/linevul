static void ext4_inode_csum_set(struct inode *inode, struct ext4_inode *raw,
				struct ext4_inode_info *ei)
{
	__u32 csum;

	if (EXT4_SB(inode->i_sb)->s_es->s_creator_os !=
	    cpu_to_le32(EXT4_OS_LINUX) ||
	    !ext4_has_metadata_csum(inode->i_sb))
		return;

	csum = ext4_inode_csum(inode, raw, ei);
	raw->i_checksum_lo = cpu_to_le16(csum & 0xFFFF);
	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi))
		raw->i_checksum_hi = cpu_to_le16(csum >> 16);
}
