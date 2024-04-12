void inet_bind_bucket_destroy(struct kmem_cache *cachep, struct inet_bind_bucket *tb)
{
	if (hlist_empty(&tb->owners)) {
		__hlist_del(&tb->node);
		release_net(ib_net(tb));
		kmem_cache_free(cachep, tb);
	}
}
