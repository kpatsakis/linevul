static inline void put_link(struct nameidata *nd)
{
	struct saved *last = nd->stack + --nd->depth;
	struct inode *inode = last->inode;
	if (last->cookie && inode->i_op->put_link)
		inode->i_op->put_link(inode, last->cookie);
	if (!(nd->flags & LOOKUP_RCU))
		path_put(&last->link);
}
