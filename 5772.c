static void end_requests(struct fuse_conn *fc, struct list_head *head)
{
	while (!list_empty(head)) {
		struct fuse_req *req;
		req = list_entry(head->next, struct fuse_req, list);
		req->out.h.error = -ECONNABORTED;
		clear_bit(FR_SENT, &req->flags);
		list_del_init(&req->list);
		request_end(fc, req);
	}
}
