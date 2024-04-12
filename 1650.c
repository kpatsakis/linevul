void iput(struct inode *inode)
{
	if (inode) {
		BUG_ON(inode->i_state & I_CLEAR);

		if (atomic_dec_and_lock(&inode->i_count, &inode->i_lock))
			iput_final(inode);
	}
}
