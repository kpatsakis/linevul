static int dn_sendmsg(struct socket *sock, struct msghdr *msg, size_t size)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	size_t mss;
	struct sk_buff_head *queue = &scp->data_xmit_queue;
	int flags = msg->msg_flags;
	int err = 0;
	size_t sent = 0;
	int addr_len = msg->msg_namelen;
	DECLARE_SOCKADDR(struct sockaddr_dn *, addr, msg->msg_name);
	struct sk_buff *skb = NULL;
	struct dn_skb_cb *cb;
	size_t len;
	unsigned char fctype;
	long timeo;

	if (flags & ~(MSG_TRYHARD|MSG_OOB|MSG_DONTWAIT|MSG_EOR|MSG_NOSIGNAL|MSG_MORE|MSG_CMSG_COMPAT))
		return -EOPNOTSUPP;

	if (addr_len && (addr_len != sizeof(struct sockaddr_dn)))
		return -EINVAL;

	lock_sock(sk);
	timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);
	/*
	 * The only difference between stream sockets and sequenced packet
	 * sockets is that the stream sockets always behave as if MSG_EOR
	 * has been set.
	 */
	if (sock->type == SOCK_STREAM) {
		if (flags & MSG_EOR) {
			err = -EINVAL;
			goto out;
		}
		flags |= MSG_EOR;
	}


	err = dn_check_state(sk, addr, addr_len, &timeo, flags);
	if (err)
		goto out_err;

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		err = -EPIPE;
		if (!(flags & MSG_NOSIGNAL))
			send_sig(SIGPIPE, current, 0);
		goto out_err;
	}

	if ((flags & MSG_TRYHARD) && sk->sk_dst_cache)
		dst_negative_advice(sk);

	mss = scp->segsize_rem;
	fctype = scp->services_rem & NSP_FC_MASK;

	mss = dn_current_mss(sk, flags);

	if (flags & MSG_OOB) {
		queue = &scp->other_xmit_queue;
		if (size > mss) {
			err = -EMSGSIZE;
			goto out;
		}
	}

	scp->persist_fxn = dn_nsp_xmit_timeout;

	while(sent < size) {
		err = sock_error(sk);
		if (err)
			goto out;

		if (signal_pending(current)) {
			err = sock_intr_errno(timeo);
			goto out;
		}

		/*
		 * Calculate size that we wish to send.
		 */
		len = size - sent;

		if (len > mss)
			len = mss;

		/*
		 * Wait for queue size to go down below the window
		 * size.
		 */
		if (dn_queue_too_long(scp, queue, flags)) {
			DEFINE_WAIT(wait);

			if (flags & MSG_DONTWAIT) {
				err = -EWOULDBLOCK;
				goto out;
			}

			prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
			sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
			sk_wait_event(sk, &timeo,
				      !dn_queue_too_long(scp, queue, flags));
			sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
			finish_wait(sk_sleep(sk), &wait);
			continue;
		}

		/*
		 * Get a suitably sized skb.
		 * 64 is a bit of a hack really, but its larger than any
		 * link-layer headers and has served us well as a good
		 * guess as to their real length.
		 */
		skb = dn_alloc_send_pskb(sk, len + 64 + DN_MAX_NSP_DATA_HEADER,
					 flags & MSG_DONTWAIT, &err);

		if (err)
			break;

		if (!skb)
			continue;

		cb = DN_SKB_CB(skb);

		skb_reserve(skb, 64 + DN_MAX_NSP_DATA_HEADER);

		if (memcpy_from_msg(skb_put(skb, len), msg, len)) {
			err = -EFAULT;
			goto out;
		}

		if (flags & MSG_OOB) {
			cb->nsp_flags = 0x30;
			if (fctype != NSP_FC_NONE)
				scp->flowrem_oth--;
		} else {
			cb->nsp_flags = 0x00;
			if (scp->seg_total == 0)
				cb->nsp_flags |= 0x20;

			scp->seg_total += len;

			if (((sent + len) == size) && (flags & MSG_EOR)) {
				cb->nsp_flags |= 0x40;
				scp->seg_total = 0;
				if (fctype == NSP_FC_SCMC)
					scp->flowrem_dat--;
			}
			if (fctype == NSP_FC_SRC)
				scp->flowrem_dat--;
		}

		sent += len;
		dn_nsp_queue_xmit(sk, skb, sk->sk_allocation, flags & MSG_OOB);
		skb = NULL;

		scp->persist = dn_nsp_persist(sk);

	}
out:

	kfree_skb(skb);

	release_sock(sk);

	return sent ? sent : err;

out_err:
	err = sk_stream_error(sk, flags, err);
	release_sock(sk);
	return err;
}
