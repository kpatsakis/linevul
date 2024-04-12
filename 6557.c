static int pppol2tp_session_ioctl(struct l2tp_session *session,
				  unsigned int cmd, unsigned long arg)
{
	struct ifreq ifr;
	int err = 0;
	struct sock *sk;
	int val = (int) arg;
	struct pppol2tp_session *ps = l2tp_session_priv(session);
	struct l2tp_tunnel *tunnel = session->tunnel;
	struct pppol2tp_ioc_stats stats;

	l2tp_dbg(session, PPPOL2TP_MSG_CONTROL,
		 "%s: pppol2tp_session_ioctl(cmd=%#x, arg=%#lx)\n",
		 session->name, cmd, arg);

	sk = ps->sock;
	sock_hold(sk);

	switch (cmd) {
	case SIOCGIFMTU:
		err = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			break;

		err = -EFAULT;
		if (copy_from_user(&ifr, (void __user *) arg, sizeof(struct ifreq)))
			break;
		ifr.ifr_mtu = session->mtu;
		if (copy_to_user((void __user *) arg, &ifr, sizeof(struct ifreq)))
			break;

		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: get mtu=%d\n",
			  session->name, session->mtu);
		err = 0;
		break;

	case SIOCSIFMTU:
		err = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			break;

		err = -EFAULT;
		if (copy_from_user(&ifr, (void __user *) arg, sizeof(struct ifreq)))
			break;

		session->mtu = ifr.ifr_mtu;

		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: set mtu=%d\n",
			  session->name, session->mtu);
		err = 0;
		break;

	case PPPIOCGMRU:
		err = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			break;

		err = -EFAULT;
		if (put_user(session->mru, (int __user *) arg))
			break;

		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: get mru=%d\n",
			  session->name, session->mru);
		err = 0;
		break;

	case PPPIOCSMRU:
		err = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			break;

		err = -EFAULT;
		if (get_user(val, (int __user *) arg))
			break;

		session->mru = val;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: set mru=%d\n",
			  session->name, session->mru);
		err = 0;
		break;

	case PPPIOCGFLAGS:
		err = -EFAULT;
		if (put_user(ps->flags, (int __user *) arg))
			break;

		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: get flags=%d\n",
			  session->name, ps->flags);
		err = 0;
		break;

	case PPPIOCSFLAGS:
		err = -EFAULT;
		if (get_user(val, (int __user *) arg))
			break;
		ps->flags = val;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: set flags=%d\n",
			  session->name, ps->flags);
		err = 0;
		break;

	case PPPIOCGL2TPSTATS:
		err = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			break;

		memset(&stats, 0, sizeof(stats));
		stats.tunnel_id = tunnel->tunnel_id;
		stats.session_id = session->session_id;
		pppol2tp_copy_stats(&stats, &session->stats);
		if (copy_to_user((void __user *) arg, &stats,
				 sizeof(stats)))
			break;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: get L2TP stats\n",
			  session->name);
		err = 0;
		break;

	default:
		err = -ENOSYS;
		break;
	}

	sock_put(sk);

	return err;
}
