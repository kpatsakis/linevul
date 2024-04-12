static void tcp_v6_reqsk_destructor(struct request_sock *req)
{
	kfree_skb(inet6_rsk(req)->pktopts);
}
