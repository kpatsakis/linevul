static int ipv6_renew_option(void *ohdr,
			     struct ipv6_opt_hdr __user *newopt, int newoptlen,
			     int inherit,
			     struct ipv6_opt_hdr **hdr,
			     char **p)
{
	if (inherit) {
		if (ohdr) {
			memcpy(*p, ohdr, ipv6_optlen((struct ipv6_opt_hdr *)ohdr));
			*hdr = (struct ipv6_opt_hdr *)*p;
			*p += CMSG_ALIGN(ipv6_optlen(*hdr));
		}
	} else {
		if (newopt) {
			if (copy_from_user(*p, newopt, newoptlen))
				return -EFAULT;
			*hdr = (struct ipv6_opt_hdr *)*p;
			if (ipv6_optlen(*hdr) > newoptlen)
				return -EINVAL;
			*p += CMSG_ALIGN(newoptlen);
		}
	}
	return 0;
}
