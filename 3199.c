static inline struct msg_msg *prepare_copy(void __user *buf, size_t bufsz)
{
	struct msg_msg *copy;

	/*
	 * Create dummy message to copy real message to.
	 */
	copy = load_msg(buf, bufsz);
	if (!IS_ERR(copy))
		copy->m_ts = bufsz;
	return copy;
}
