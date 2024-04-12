int sk_set_peek_off(struct sock *sk, int val)
{
	if (val < 0)
		return -EINVAL;

	sk->sk_peek_off = val;
	return 0;
}
