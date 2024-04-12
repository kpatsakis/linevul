osf_filldir(void *__buf, const char *name, int namlen, loff_t offset,
	    u64 ino, unsigned int d_type)
{
	struct osf_dirent __user *dirent;
	struct osf_dirent_callback *buf = (struct osf_dirent_callback *) __buf;
	unsigned int reclen = ALIGN(NAME_OFFSET + namlen + 1, sizeof(u32));
	unsigned int d_ino;

	buf->error = -EINVAL;	/* only used if we fail */
	if (reclen > buf->count)
		return -EINVAL;
	d_ino = ino;
	if (sizeof(d_ino) < sizeof(ino) && d_ino != ino) {
		buf->error = -EOVERFLOW;
		return -EOVERFLOW;
	}
	if (buf->basep) {
		if (put_user(offset, buf->basep))
			goto Efault;
		buf->basep = NULL;
	}
	dirent = buf->dirent;
	if (put_user(d_ino, &dirent->d_ino) ||
	    put_user(namlen, &dirent->d_namlen) ||
	    put_user(reclen, &dirent->d_reclen) ||
	    copy_to_user(dirent->d_name, name, namlen) ||
	    put_user(0, dirent->d_name + namlen))
		goto Efault;
	dirent = (void __user *)dirent + reclen;
	buf->dirent = dirent;
	buf->count -= reclen;
	return 0;
Efault:
	buf->error = -EFAULT;
	return -EFAULT;
}
