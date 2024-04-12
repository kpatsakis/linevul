static int handle_fsync(struct fuse* fuse, struct fuse_handler* handler,
 const struct fuse_in_header* hdr, const struct fuse_fsync_in* req)
{
 bool is_dir = (hdr->opcode == FUSE_FSYNCDIR);
 bool is_data_sync = req->fsync_flags & 1;

 int fd = -1;
 if (is_dir) {
 struct dirhandle *dh = id_to_ptr(req->fh);
      fd = dirfd(dh->d);
 } else {
 struct handle *h = id_to_ptr(req->fh);
      fd = h->fd;
 }

    TRACE("[%d] %s %p(%d) is_data_sync=%d\n", handler->token,
            is_dir ? "FSYNCDIR" : "FSYNC",
            id_to_ptr(req->fh), fd, is_data_sync);
 int res = is_data_sync ? fdatasync(fd) : fsync(fd);
 if (res == -1) {
 return -errno;
 }
 return 0;
}
