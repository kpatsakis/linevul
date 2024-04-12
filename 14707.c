static inline struct sock *get_cookie_sock(struct sock *sk, struct sk_buff *skb,
					   struct request_sock *req,
					   struct dst_entry *dst)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct sock *child;

	child = icsk->icsk_af_ops->syn_recv_sock(sk, skb, req, dst);
	if (child)
		inet_csk_reqsk_queue_add(sk, req, child);
	else
		reqsk_free(req);

	return child;
}
