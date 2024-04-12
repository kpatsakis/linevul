static int dccp_v4_init_sock(struct sock *sk)
{
	static __u8 dccp_v4_ctl_sock_initialized;
	int err = dccp_init_sock(sk, dccp_v4_ctl_sock_initialized);

	if (err == 0) {
		if (unlikely(!dccp_v4_ctl_sock_initialized))
			dccp_v4_ctl_sock_initialized = 1;
		inet_csk(sk)->icsk_af_ops = &dccp_ipv4_af_ops;
	}

	return err;
}
