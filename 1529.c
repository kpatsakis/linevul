void skcipher_walk_complete(struct skcipher_walk *walk, int err)
{
	struct skcipher_walk_buffer *p, *tmp;

	list_for_each_entry_safe(p, tmp, &walk->buffers, entry) {
		u8 *data;

		if (err)
			goto done;

		data = p->data;
		if (!data) {
			data = PTR_ALIGN(&p->buffer[0], walk->alignmask + 1);
			data = skcipher_get_spot(data, walk->stride);
		}

		scatterwalk_copychunks(data, &p->dst, p->len, 1);

		if (offset_in_page(p->data) + p->len + walk->stride >
		    PAGE_SIZE)
			free_page((unsigned long)p->data);

done:
		list_del(&p->entry);
		kfree(p);
	}

	if (!err && walk->iv != walk->oiv)
		memcpy(walk->oiv, walk->iv, walk->ivsize);
	if (walk->buffer != walk->page)
		kfree(walk->buffer);
	if (walk->page)
		free_page((unsigned long)walk->page);
}
