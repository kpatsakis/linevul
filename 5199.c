static void hugetlbfs_i_callback(struct rcu_head *head)
{
	struct inode *inode = container_of(head, struct inode, i_rcu);
	kmem_cache_free(hugetlbfs_inode_cachep, HUGETLBFS_I(inode));
}
