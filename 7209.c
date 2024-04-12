static int irda_sendmsg_ultra(struct socket *sock, struct msghdr *msg,
			      size_t len)
{
	struct sock *sk = sock->sk;
	struct irda_sock *self;
	__u8 pid = 0;
	int bound = 0;
	struct sk_buff *skb;
	int err;

	pr_debug("%s(), len=%zd\n", __func__, len);

	err = -EINVAL;
	if (msg->msg_flags & ~(MSG_DONTWAIT|MSG_CMSG_COMPAT))
		return -EINVAL;

	lock_sock(sk);

	err = -EPIPE;
	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		send_sig(SIGPIPE, current, 0);
		goto out;
	}

	self = irda_sk(sk);

	/* Check if an address was specified with sendto. Jean II */
	if (msg->msg_name) {
		DECLARE_SOCKADDR(struct sockaddr_irda *, addr, msg->msg_name);
		err = -EINVAL;
		/* Check address, extract pid. Jean II */
		if (msg->msg_namelen < sizeof(*addr))
			goto out;
		if (addr->sir_family != AF_IRDA)
			goto out;

		pid = addr->sir_lsap_sel;
		if (pid & 0x80) {
			pr_debug("%s(), extension in PID not supp!\n",
				 __func__);
			err = -EOPNOTSUPP;
			goto out;
		}
	} else {
		/* Check that the socket is properly bound to an Ultra
		 * port. Jean II */
		if ((self->lsap == NULL) ||
		    (sk->sk_state != TCP_ESTABLISHED)) {
			pr_debug("%s(), socket not bound to Ultra PID.\n",
				 __func__);
			err = -ENOTCONN;
			goto out;
		}
		/* Use PID from socket */
		bound = 1;
	}

	/*
	 * Check that we don't send out too big frames. This is an unreliable
	 * service, so we have no fragmentation and no coalescence
	 */
	if (len > self->max_data_size) {
		pr_debug("%s(), Warning too much data! Chopping frame from %zd to %d bytes!\n",
			 __func__, len, self->max_data_size);
		len = self->max_data_size;
	}

	skb = sock_alloc_send_skb(sk, len + self->max_header_size,
				  msg->msg_flags & MSG_DONTWAIT, &err);
	err = -ENOBUFS;
	if (!skb)
		goto out;

	skb_reserve(skb, self->max_header_size);
	skb_reset_transport_header(skb);

	pr_debug("%s(), appending user data\n", __func__);
	skb_put(skb, len);
	err = memcpy_from_msg(skb_transport_header(skb), msg, len);
	if (err) {
		kfree_skb(skb);
		goto out;
	}

	err = irlmp_connless_data_request((bound ? self->lsap : NULL),
					  skb, pid);
	if (err)
		pr_debug("%s(), err=%d\n", __func__, err);
out:
	release_sock(sk);
	return err ? : len;
}
