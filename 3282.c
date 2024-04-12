static void fr_timer(unsigned long arg)
{
	struct net_device *dev = (struct net_device *)arg;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	int i, cnt = 0, reliable;
	u32 list;

	if (state(hdlc)->settings.dce) {
		reliable = state(hdlc)->request &&
			time_before(jiffies, state(hdlc)->last_poll +
				    state(hdlc)->settings.t392 * HZ);
		state(hdlc)->request = 0;
	} else {
		state(hdlc)->last_errors <<= 1; /* Shift the list */
		if (state(hdlc)->request) {
			if (state(hdlc)->reliable)
				netdev_info(dev, "No LMI status reply received\n");
			state(hdlc)->last_errors |= 1;
		}

		list = state(hdlc)->last_errors;
		for (i = 0; i < state(hdlc)->settings.n393; i++, list >>= 1)
			cnt += (list & 1);	/* errors count */

		reliable = (cnt < state(hdlc)->settings.n392);
	}

	if (state(hdlc)->reliable != reliable) {
		netdev_info(dev, "Link %sreliable\n", reliable ? "" : "un");
		fr_set_link_state(reliable, dev);
	}

	if (state(hdlc)->settings.dce)
		state(hdlc)->timer.expires = jiffies +
			state(hdlc)->settings.t392 * HZ;
	else {
		if (state(hdlc)->n391cnt)
			state(hdlc)->n391cnt--;

		fr_lmi_send(dev, state(hdlc)->n391cnt == 0);

		state(hdlc)->last_poll = jiffies;
		state(hdlc)->request = 1;
		state(hdlc)->timer.expires = jiffies +
			state(hdlc)->settings.t391 * HZ;
	}

	state(hdlc)->timer.function = fr_timer;
	state(hdlc)->timer.data = arg;
	add_timer(&state(hdlc)->timer);
}
