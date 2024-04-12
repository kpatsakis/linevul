static ssize_t ib_ucm_send_drep(struct ib_ucm_file *file,
				const char __user *inbuf,
				int in_len, int out_len)
{
	return ib_ucm_send_private_data(file, inbuf, in_len, ib_send_cm_drep);
}
