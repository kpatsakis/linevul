static int dvd_read_manufact(struct cdrom_device_info *cdi, dvd_struct *s,
				struct packet_command *cgc)
{
	int ret = 0, size;
	u_char *buf;
	const struct cdrom_device_ops *cdo = cdi->ops;

	size = sizeof(s->manufact.value) + 4;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	init_cdrom_command(cgc, buf, size, CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[7] = s->type;
	cgc->cmd[8] = size >> 8;
	cgc->cmd[9] = size & 0xff;

	ret = cdo->generic_packet(cdi, cgc);
	if (ret)
		goto out;

	s->manufact.len = buf[0] << 8 | buf[1];
	if (s->manufact.len < 0) {
		cd_dbg(CD_WARNING, "Received invalid manufacture info length (%d)\n",
		       s->manufact.len);
		ret = -EIO;
	} else {
		if (s->manufact.len > 2048) {
			cd_dbg(CD_WARNING, "Received invalid manufacture info length (%d): truncating to 2048\n",
			       s->manufact.len);
			s->manufact.len = 2048;
		}
		memcpy(s->manufact.value, &buf[4], s->manufact.len);
	}

out:
	kfree(buf);
	return ret;
}
