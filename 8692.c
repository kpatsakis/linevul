static int fiber_autoneg(struct tg3 *tp, u32 *txflags, u32 *rxflags)
{
	int res = 0;
	struct tg3_fiber_aneginfo aninfo;
	int status = ANEG_FAILED;
	unsigned int tick;
	u32 tmp;

	tw32_f(MAC_TX_AUTO_NEG, 0);

	tmp = tp->mac_mode & ~MAC_MODE_PORT_MODE_MASK;
	tw32_f(MAC_MODE, tmp | MAC_MODE_PORT_MODE_GMII);
	udelay(40);

	tw32_f(MAC_MODE, tp->mac_mode | MAC_MODE_SEND_CONFIGS);
	udelay(40);

	memset(&aninfo, 0, sizeof(aninfo));
	aninfo.flags |= MR_AN_ENABLE;
	aninfo.state = ANEG_STATE_UNKNOWN;
	aninfo.cur_time = 0;
	tick = 0;
	while (++tick < 195000) {
		status = tg3_fiber_aneg_smachine(tp, &aninfo);
		if (status == ANEG_DONE || status == ANEG_FAILED)
			break;

		udelay(1);
	}

	tp->mac_mode &= ~MAC_MODE_SEND_CONFIGS;
	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	*txflags = aninfo.txconfig;
	*rxflags = aninfo.flags;

	if (status == ANEG_DONE &&
	    (aninfo.flags & (MR_AN_COMPLETE | MR_LINK_OK |
			     MR_LP_ADV_FULL_DUPLEX)))
		res = 1;

	return res;
}
