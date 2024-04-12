static int read_header(struct pstore *ps, int *new_snapshot)
{
	int r;
	struct disk_header *dh;
	unsigned chunk_size;
	int chunk_size_supplied = 1;
	char *chunk_err;

	/*
	 * Use default chunk size (or logical_block_size, if larger)
	 * if none supplied
	 */
	if (!ps->store->chunk_size) {
		ps->store->chunk_size = max(DM_CHUNK_SIZE_DEFAULT_SECTORS,
		    bdev_logical_block_size(dm_snap_cow(ps->store->snap)->
					    bdev) >> 9);
		ps->store->chunk_mask = ps->store->chunk_size - 1;
		ps->store->chunk_shift = ffs(ps->store->chunk_size) - 1;
		chunk_size_supplied = 0;
	}

	ps->io_client = dm_io_client_create();
	if (IS_ERR(ps->io_client))
		return PTR_ERR(ps->io_client);

	r = alloc_area(ps);
	if (r)
		return r;

	r = chunk_io(ps, ps->header_area, 0, READ, 1);
	if (r)
		goto bad;

	dh = ps->header_area;

	if (le32_to_cpu(dh->magic) == 0) {
		*new_snapshot = 1;
		return 0;
	}

	if (le32_to_cpu(dh->magic) != SNAP_MAGIC) {
		DMWARN("Invalid or corrupt snapshot");
		r = -ENXIO;
		goto bad;
	}

	*new_snapshot = 0;
	ps->valid = le32_to_cpu(dh->valid);
	ps->version = le32_to_cpu(dh->version);
	chunk_size = le32_to_cpu(dh->chunk_size);

	if (ps->store->chunk_size == chunk_size)
		return 0;

	if (chunk_size_supplied)
		DMWARN("chunk size %u in device metadata overrides "
		       "table chunk size of %u.",
		       chunk_size, ps->store->chunk_size);

	/* We had a bogus chunk_size. Fix stuff up. */
	free_area(ps);

	r = dm_exception_store_set_chunk_size(ps->store, chunk_size,
					      &chunk_err);
	if (r) {
		DMERR("invalid on-disk chunk size %u: %s.",
		      chunk_size, chunk_err);
		return r;
	}

	r = alloc_area(ps);
	return r;

bad:
	free_area(ps);
	return r;
}
