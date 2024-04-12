static int handle_releasedir(struct fuse* fuse, struct fuse_handler* handler,
 const struct fuse_in_header* hdr, const struct fuse_release_in* req)
{
 struct dirhandle *h = id_to_ptr(req->fh);

    TRACE("[%d] RELEASEDIR %p\n", handler->token, h);
    closedir(h->d);
    free(h);
 return 0;
}
