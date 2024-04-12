static void do_metadata(struct work_struct *work)
{
	struct mdata_req *req = container_of(work, struct mdata_req, work);

	req->result = dm_io(req->io_req, 1, req->where, NULL);
}
