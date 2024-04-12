static inline struct ip_tunnel **ipgre_bucket(struct ipgre_net *ign,
		struct ip_tunnel *t)
{
	return __ipgre_bucket(ign, &t->parms);
}
