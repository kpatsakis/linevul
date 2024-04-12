int compat_udp_setsockopt(struct sock *sk, int level, int optname,
			  char __user *optval, unsigned int optlen)
{
	if (level == SOL_UDP  ||  level == SOL_UDPLITE)
		return udp_lib_setsockopt(sk, level, optname, optval, optlen,
					  udp_push_pending_frames);
	return compat_ip_setsockopt(sk, level, optname, optval, optlen);
}
