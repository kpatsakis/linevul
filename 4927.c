int put_cmsg_compat(struct msghdr *kmsg, int level, int type, int len, void *data)
{
	struct compat_cmsghdr __user *cm = (struct compat_cmsghdr __user *) kmsg->msg_control;
	struct compat_cmsghdr cmhdr;
	struct compat_timeval ctv;
	struct compat_timespec cts[3];
	int cmlen;

	if (cm == NULL || kmsg->msg_controllen < sizeof(*cm)) {
		kmsg->msg_flags |= MSG_CTRUNC;
		return 0; /* XXX: return error? check spec. */
	}

	if (!COMPAT_USE_64BIT_TIME) {
		if (level == SOL_SOCKET && type == SCM_TIMESTAMP) {
			struct timeval *tv = (struct timeval *)data;
			ctv.tv_sec = tv->tv_sec;
			ctv.tv_usec = tv->tv_usec;
			data = &ctv;
			len = sizeof(ctv);
		}
		if (level == SOL_SOCKET &&
		    (type == SCM_TIMESTAMPNS || type == SCM_TIMESTAMPING)) {
			int count = type == SCM_TIMESTAMPNS ? 1 : 3;
			int i;
			struct timespec *ts = (struct timespec *)data;
			for (i = 0; i < count; i++) {
				cts[i].tv_sec = ts[i].tv_sec;
				cts[i].tv_nsec = ts[i].tv_nsec;
			}
			data = &cts;
			len = sizeof(cts[0]) * count;
		}
	}

	cmlen = CMSG_COMPAT_LEN(len);
	if (kmsg->msg_controllen < cmlen) {
		kmsg->msg_flags |= MSG_CTRUNC;
		cmlen = kmsg->msg_controllen;
	}
	cmhdr.cmsg_level = level;
	cmhdr.cmsg_type = type;
	cmhdr.cmsg_len = cmlen;

	if (copy_to_user(cm, &cmhdr, sizeof cmhdr))
		return -EFAULT;
	if (copy_to_user(CMSG_COMPAT_DATA(cm), data, cmlen - sizeof(struct compat_cmsghdr)))
		return -EFAULT;
	cmlen = CMSG_COMPAT_SPACE(len);
	if (kmsg->msg_controllen < cmlen)
		cmlen = kmsg->msg_controllen;
	kmsg->msg_control += cmlen;
	kmsg->msg_controllen -= cmlen;
	return 0;
}
