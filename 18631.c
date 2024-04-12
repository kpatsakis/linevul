struct sock *llc_sk_alloc(struct net *net, int family, gfp_t priority, struct proto *prot, int kern)
{
	struct sock *sk = sk_alloc(net, family, priority, prot, kern);

	if (!sk)
		goto out;
	llc_sk_init(sk);
	sock_init_data(NULL, sk);
#ifdef LLC_REFCNT_DEBUG
	atomic_inc(&llc_sock_nr);
	printk(KERN_DEBUG "LLC socket %p created in %s, now we have %d alive\n", sk,
		__func__, atomic_read(&llc_sock_nr));
#endif
out:
	return sk;
}
