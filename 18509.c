void *ext4_kvzalloc(size_t size, gfp_t flags)
{
	void *ret;

	ret = kzalloc(size, flags | __GFP_NOWARN);
	if (!ret)
		ret = __vmalloc(size, flags | __GFP_ZERO, PAGE_KERNEL);
	return ret;
}
