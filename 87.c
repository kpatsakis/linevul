static inline int iucv_below_msglim(struct sock *sk)
{
	struct iucv_sock *iucv = iucv_sk(sk);

	if (sk->sk_state != IUCV_CONNECTED)
		return 1;
	if (iucv->transport == AF_IUCV_TRANS_IUCV)
		return (skb_queue_len(&iucv->send_skb_q) < iucv->path->msglim);
	else
		return ((atomic_read(&iucv->msg_sent) < iucv->msglimit_peer) &&
			(atomic_read(&iucv->pendings) <= 0));
}
