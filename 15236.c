int ip6_frag_match(struct inet_frag_queue *q, void *a)
{
	struct frag_queue *fq;
	struct ip6_create_arg *arg = a;

	fq = container_of(q, struct frag_queue, q);
	return (fq->id == arg->id && fq->user == arg->user &&
			ipv6_addr_equal(&fq->saddr, arg->src) &&
			ipv6_addr_equal(&fq->daddr, arg->dst));
 }
