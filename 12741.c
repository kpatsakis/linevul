do_block_io_op(struct xen_blkif_ring *ring)
{
	union blkif_back_rings *blk_rings = &ring->blk_rings;
	int more_to_do;

	do {
		more_to_do = __do_block_io_op(ring);
		if (more_to_do)
			break;

		RING_FINAL_CHECK_FOR_REQUESTS(&blk_rings->common, more_to_do);
	} while (more_to_do);

	return more_to_do;
}
