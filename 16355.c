static void fwnet_free_ptask(struct fwnet_packet_task *ptask)
{
	dev_kfree_skb_any(ptask->skb);
	kmem_cache_free(fwnet_packet_task_cache, ptask);
}
