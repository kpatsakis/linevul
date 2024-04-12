static int tcp_v6_md5_hash_pseudoheader(struct tcp_md5sig_pool *hp,
					const struct in6_addr *daddr,
					const struct in6_addr *saddr, int nbytes)
{
	struct tcp6_pseudohdr *bp;
	struct scatterlist sg;

	bp = &hp->md5_blk.ip6;
	/* 1. TCP pseudo-header (RFC2460) */
	ipv6_addr_copy(&bp->saddr, saddr);
	ipv6_addr_copy(&bp->daddr, daddr);
	bp->protocol = cpu_to_be32(IPPROTO_TCP);
	bp->len = cpu_to_be32(nbytes);

	sg_init_one(&sg, bp, sizeof(*bp));
	return crypto_hash_update(&hp->md5_desc, &sg, sizeof(*bp));
}
