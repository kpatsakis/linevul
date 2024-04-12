static int addrconf_dad_end(struct inet6_ifaddr *ifp)
{
	int err = -ENOENT;

	spin_lock_bh(&ifp->state_lock);
	if (ifp->state == INET6_IFADDR_STATE_DAD) {
		ifp->state = INET6_IFADDR_STATE_POSTDAD;
		err = 0;
	}
	spin_unlock_bh(&ifp->state_lock);

	return err;
}
