ext4_xattr_block_find(struct inode *inode, struct ext4_xattr_info *i,
		      struct ext4_xattr_block_find *bs)
{
	struct super_block *sb = inode->i_sb;
	int error;

	ea_idebug(inode, "name=%d.%s, value=%p, value_len=%ld",
		  i->name_index, i->name, i->value, (long)i->value_len);

	if (EXT4_I(inode)->i_file_acl) {
		/* The inode already has an extended attribute block. */
		bs->bh = sb_bread(sb, EXT4_I(inode)->i_file_acl);
		error = -EIO;
		if (!bs->bh)
			goto cleanup;
		ea_bdebug(bs->bh, "b_count=%d, refcount=%d",
			atomic_read(&(bs->bh->b_count)),
			le32_to_cpu(BHDR(bs->bh)->h_refcount));
		if (ext4_xattr_check_block(inode, bs->bh)) {
			EXT4_ERROR_INODE(inode, "bad block %llu",
					 EXT4_I(inode)->i_file_acl);
			error = -EFSCORRUPTED;
			goto cleanup;
		}
		/* Find the named attribute. */
		bs->s.base = BHDR(bs->bh);
		bs->s.first = BFIRST(bs->bh);
		bs->s.end = bs->bh->b_data + bs->bh->b_size;
		bs->s.here = bs->s.first;
		error = ext4_xattr_find_entry(&bs->s.here, i->name_index,
					      i->name, bs->bh->b_size, 1);
		if (error && error != -ENODATA)
			goto cleanup;
		bs->s.not_found = error;
	}
	error = 0;

cleanup:
	return error;
}
