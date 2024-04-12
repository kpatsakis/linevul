static int dcbnl_notify(struct net_device *dev, int event, int cmd,
			u32 seq, u32 portid, int dcbx_ver)
{
	struct net *net = dev_net(dev);
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	const struct dcbnl_rtnl_ops *ops = dev->dcbnl_ops;
	int err;

	if (!ops)
		return -EOPNOTSUPP;

	skb = dcbnl_newmsg(event, cmd, portid, seq, 0, &nlh);
	if (!skb)
		return -ENOBUFS;

	if (dcbx_ver == DCB_CAP_DCBX_VER_IEEE)
		err = dcbnl_ieee_fill(skb, dev);
	else
		err = dcbnl_cee_fill(skb, dev);

	if (err < 0) {
		/* Report error to broadcast listeners */
		nlmsg_free(skb);
		rtnl_set_sk_err(net, RTNLGRP_DCB, err);
	} else {
		/* End nlmsg and notify broadcast listeners */
		nlmsg_end(skb, nlh);
		rtnl_notify(skb, net, 0, RTNLGRP_DCB, NULL, GFP_KERNEL);
	}

	return err;
}
