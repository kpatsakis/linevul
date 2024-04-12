struct fuse_req *fuse_get_req_for_background(struct fuse_conn *fc,
					     unsigned npages)
{
	return __fuse_get_req(fc, npages, true);
}
