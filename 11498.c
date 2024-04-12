static void pcd_request(void)
{
	struct pcd_unit *cd;

	if (pcd_busy)
		return;

	if (!pcd_req && !set_next_request())
		return;

	cd = pcd_req->rq_disk->private_data;
	if (cd != pcd_current)
		pcd_bufblk = -1;
	pcd_current = cd;
	pcd_sector = blk_rq_pos(pcd_req);
	pcd_count = blk_rq_cur_sectors(pcd_req);
	pcd_buf = bio_data(pcd_req->bio);
	pcd_busy = 1;
	ps_set_intr(do_pcd_read, NULL, 0, nice);
}
