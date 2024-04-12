static inline int rt_is_expired(struct rtable *rth)
{
	return rth->rt_genid != rt_genid(dev_net(rth->dst.dev));
}
