struct socket *tun_get_socket(struct file *file)
{
	struct tun_struct *tun;
	if (file->f_op != &tun_fops)
		return ERR_PTR(-EINVAL);
	tun = tun_get(file);
	if (!tun)
		return ERR_PTR(-EBADFD);
	tun_put(tun);
	return &tun->socket;
}
