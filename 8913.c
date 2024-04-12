static int airo_set_scan(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *dwrq,
			 char *extra)
{
	struct airo_info *ai = dev->ml_priv;
	Cmd cmd;
	Resp rsp;
	int wake = 0;

	/* Note : you may have realised that, as this is a SET operation,
	 * this is privileged and therefore a normal user can't
	 * perform scanning.
	 * This is not an error, while the device perform scanning,
	 * traffic doesn't flow, so it's a perfect DoS...
	 * Jean II */
	if (ai->flags & FLAG_RADIO_MASK) return -ENETDOWN;

	if (down_interruptible(&ai->sem))
		return -ERESTARTSYS;

	/* If there's already a scan in progress, don't
	 * trigger another one. */
	if (ai->scan_timeout > 0)
		goto out;

	/* Initiate a scan command */
	ai->scan_timeout = RUN_AT(3*HZ);
	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd=CMD_LISTBSS;
	issuecommand(ai, &cmd, &rsp);
	wake = 1;

out:
	up(&ai->sem);
	if (wake)
		wake_up_interruptible(&ai->thr_wait);
	return 0;
}
