static void drop_links(struct nameidata *nd)
{
	int i = nd->depth;
	while (i--) {
		struct saved *last = nd->stack + i;
		struct inode *inode = last->inode;
		if (last->cookie && inode->i_op->put_link) {
			inode->i_op->put_link(inode, last->cookie);
			last->cookie = NULL;
		}
	}
}
