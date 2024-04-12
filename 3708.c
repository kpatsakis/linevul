static int netlink_mmap(struct file *file, struct socket *sock,
			struct vm_area_struct *vma)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_ring *ring;
	unsigned long start, size, expected;
	unsigned int i;
	int err = -EINVAL;

	if (vma->vm_pgoff)
		return -EINVAL;

	mutex_lock(&nlk->pg_vec_lock);

	expected = 0;
	for (ring = &nlk->rx_ring; ring <= &nlk->tx_ring; ring++) {
		if (ring->pg_vec == NULL)
			continue;
		expected += ring->pg_vec_len * ring->pg_vec_pages * PAGE_SIZE;
	}

	if (expected == 0)
		goto out;

	size = vma->vm_end - vma->vm_start;
	if (size != expected)
		goto out;

	start = vma->vm_start;
	for (ring = &nlk->rx_ring; ring <= &nlk->tx_ring; ring++) {
		if (ring->pg_vec == NULL)
			continue;

		for (i = 0; i < ring->pg_vec_len; i++) {
			struct page *page;
			void *kaddr = ring->pg_vec[i];
			unsigned int pg_num;

			for (pg_num = 0; pg_num < ring->pg_vec_pages; pg_num++) {
				page = pgvec_to_page(kaddr);
				err = vm_insert_page(vma, start, page);
				if (err < 0)
					goto out;
				start += PAGE_SIZE;
				kaddr += PAGE_SIZE;
			}
		}
	}

	atomic_inc(&nlk->mapped);
	vma->vm_ops = &netlink_mmap_ops;
	err = 0;
out:
	mutex_unlock(&nlk->pg_vec_lock);
	return err;
}
