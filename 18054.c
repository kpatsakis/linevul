static int handle_write(struct fuse* fuse, struct fuse_handler* handler,
 const struct fuse_in_header* hdr, const struct fuse_write_in* req,
 const void* buffer)
{
 struct fuse_write_out out;
 struct handle *h = id_to_ptr(req->fh);
 int res;
    __u8 aligned_buffer[req->size] __attribute__((__aligned__(PAGESIZE)));

 if (req->flags & O_DIRECT) {
        memcpy(aligned_buffer, buffer, req->size);
        buffer = (const __u8*) aligned_buffer;
 }

    TRACE("[%d] WRITE %p(%d) %u@%"PRIu64"\n", handler->token,
            h, h->fd, req->size, req->offset);
    res = pwrite64(h->fd, buffer, req->size, req->offset);
 if (res < 0) {
 return -errno;
 }
    out.size = res;
    out.padding = 0;
    fuse_reply(fuse, hdr->unique, &out, sizeof(out));
 return NO_STATUS;
}
