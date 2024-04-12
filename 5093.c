int fscrypt_decrypt_page(const struct inode *inode, struct page *page,
			unsigned int len, unsigned int offs, u64 lblk_num)
{
	if (!(inode->i_sb->s_cop->flags & FS_CFLG_OWN_PAGES))
		BUG_ON(!PageLocked(page));

	return fscrypt_do_page_crypto(inode, FS_DECRYPT, lblk_num, page, page,
				      len, offs, GFP_NOFS);
}
