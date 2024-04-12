test_deny(u32 deny, struct nfs4_ol_stateid *stp)
{
	unsigned char mask = 1 << deny;

	return (bool)(stp->st_deny_bmap & mask);
}
