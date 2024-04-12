static int __dn_setsockopt(struct socket *sock, int level,int optname, char __user *optval, unsigned int optlen, int flags)
{
	struct	sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	long timeo;
	union {
		struct optdata_dn opt;
		struct accessdata_dn acc;
		int mode;
		unsigned long win;
		int val;
		unsigned char services;
		unsigned char info;
	} u;
	int err;

	if (optlen && !optval)
		return -EINVAL;

	if (optlen > sizeof(u))
		return -EINVAL;

	if (copy_from_user(&u, optval, optlen))
		return -EFAULT;

	switch (optname) {
	case DSO_CONDATA:
		if (sock->state == SS_CONNECTED)
			return -EISCONN;
		if ((scp->state != DN_O) && (scp->state != DN_CR))
			return -EINVAL;

		if (optlen != sizeof(struct optdata_dn))
			return -EINVAL;

		if (le16_to_cpu(u.opt.opt_optl) > 16)
			return -EINVAL;

		memcpy(&scp->conndata_out, &u.opt, optlen);
		break;

	case DSO_DISDATA:
		if (sock->state != SS_CONNECTED &&
		    scp->accept_mode == ACC_IMMED)
			return -ENOTCONN;

		if (optlen != sizeof(struct optdata_dn))
			return -EINVAL;

		if (le16_to_cpu(u.opt.opt_optl) > 16)
			return -EINVAL;

		memcpy(&scp->discdata_out, &u.opt, optlen);
		break;

	case DSO_CONACCESS:
		if (sock->state == SS_CONNECTED)
			return -EISCONN;
		if (scp->state != DN_O)
			return -EINVAL;

		if (optlen != sizeof(struct accessdata_dn))
			return -EINVAL;

		if ((u.acc.acc_accl > DN_MAXACCL) ||
		    (u.acc.acc_passl > DN_MAXACCL) ||
		    (u.acc.acc_userl > DN_MAXACCL))
			return -EINVAL;

		memcpy(&scp->accessdata, &u.acc, optlen);
		break;

	case DSO_ACCEPTMODE:
		if (sock->state == SS_CONNECTED)
			return -EISCONN;
		if (scp->state != DN_O)
			return -EINVAL;

		if (optlen != sizeof(int))
			return -EINVAL;

		if ((u.mode != ACC_IMMED) && (u.mode != ACC_DEFER))
			return -EINVAL;

		scp->accept_mode = (unsigned char)u.mode;
		break;

	case DSO_CONACCEPT:
		if (scp->state != DN_CR)
			return -EINVAL;
		timeo = sock_rcvtimeo(sk, 0);
		err = dn_confirm_accept(sk, &timeo, sk->sk_allocation);
		return err;

	case DSO_CONREJECT:
		if (scp->state != DN_CR)
			return -EINVAL;

		scp->state = DN_DR;
		sk->sk_shutdown = SHUTDOWN_MASK;
		dn_nsp_send_disc(sk, 0x38, 0, sk->sk_allocation);
		break;

	default:
#ifdef CONFIG_NETFILTER
		return nf_setsockopt(sk, PF_DECnet, optname, optval, optlen);
#endif
	case DSO_LINKINFO:
	case DSO_STREAM:
	case DSO_SEQPACKET:
		return -ENOPROTOOPT;

	case DSO_MAXWINDOW:
		if (optlen != sizeof(unsigned long))
			return -EINVAL;
		if (u.win > NSP_MAX_WINDOW)
			u.win = NSP_MAX_WINDOW;
		if (u.win == 0)
			return -EINVAL;
		scp->max_window = u.win;
		if (scp->snd_window > u.win)
			scp->snd_window = u.win;
		break;

	case DSO_NODELAY:
		if (optlen != sizeof(int))
			return -EINVAL;
		if (scp->nonagle == 2)
			return -EINVAL;
		scp->nonagle = (u.val == 0) ? 0 : 1;
		/* if (scp->nonagle == 1) { Push pending frames } */
		break;

	case DSO_CORK:
		if (optlen != sizeof(int))
			return -EINVAL;
		if (scp->nonagle == 1)
			return -EINVAL;
		scp->nonagle = (u.val == 0) ? 0 : 2;
		/* if (scp->nonagle == 0) { Push pending frames } */
		break;

	case DSO_SERVICES:
		if (optlen != sizeof(unsigned char))
			return -EINVAL;
		if ((u.services & ~NSP_FC_MASK) != 0x01)
			return -EINVAL;
		if ((u.services & NSP_FC_MASK) == NSP_FC_MASK)
			return -EINVAL;
		scp->services_loc = u.services;
		break;

	case DSO_INFO:
		if (optlen != sizeof(unsigned char))
			return -EINVAL;
		if (u.info & 0xfc)
			return -EINVAL;
		scp->info_loc = u.info;
		break;
	}

	return 0;
}
