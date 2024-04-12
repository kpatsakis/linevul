static int inet_csk_bind_conflict(const struct sock *sk,
				  const struct inet_bind_bucket *tb,
				  bool relax, bool reuseport_ok)
{
	struct sock *sk2;
	bool reuse = sk->sk_reuse;
	bool reuseport = !!sk->sk_reuseport && reuseport_ok;
	kuid_t uid = sock_i_uid((struct sock *)sk);

	/*
	 * Unlike other sk lookup places we do not check
	 * for sk_net here, since _all_ the socks listed
	 * in tb->owners list belong to the same net - the
	 * one this bucket belongs to.
	 */

	sk_for_each_bound(sk2, &tb->owners) {
		if (sk != sk2 &&
		    (!sk->sk_bound_dev_if ||
		     !sk2->sk_bound_dev_if ||
		     sk->sk_bound_dev_if == sk2->sk_bound_dev_if)) {
			if ((!reuse || !sk2->sk_reuse ||
			    sk2->sk_state == TCP_LISTEN) &&
			    (!reuseport || !sk2->sk_reuseport ||
			     rcu_access_pointer(sk->sk_reuseport_cb) ||
			     (sk2->sk_state != TCP_TIME_WAIT &&
			     !uid_eq(uid, sock_i_uid(sk2))))) {
				if (inet_rcv_saddr_equal(sk, sk2, true))
					break;
			}
			if (!relax && reuse && sk2->sk_reuse &&
			    sk2->sk_state != TCP_LISTEN) {
				if (inet_rcv_saddr_equal(sk, sk2, true))
					break;
			}
		}
	}
	return sk2 != NULL;
}
