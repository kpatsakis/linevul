void fuse_sync_release(struct fuse_file *ff, int flags)
{
	WARN_ON(atomic_read(&ff->count) > 1);
	fuse_prepare_release(ff, flags, FUSE_RELEASE);
	__set_bit(FR_FORCE, &ff->reserved_req->flags);
	__clear_bit(FR_BACKGROUND, &ff->reserved_req->flags);
	fuse_request_send(ff->fc, ff->reserved_req);
	fuse_put_request(ff->fc, ff->reserved_req);
	kfree(ff);
}
