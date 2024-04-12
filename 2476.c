decode_rfc3442_rt(int dl, const uint8_t *data)
{
 const uint8_t *p = data;
 const uint8_t *e;
 uint8_t cidr;
 size_t ocets;
 struct rt *routes = NULL;
 struct rt *rt = NULL;

 /* Minimum is 5 -first is CIDR and a router length of 4 */
 if (dl < 5)
 return NULL;

	e = p + dl;
 while (p < e) {
		cidr = *p++;
 if (cidr > 32) {
			free_routes(routes);
			errno = EINVAL;
 return NULL;
 }

 if (rt) {
			rt->next = xzalloc(sizeof(*rt));
			rt = rt->next;
 } else {
			routes = rt = xzalloc(sizeof(*routes));
 }
		rt->next = NULL;

		ocets = (cidr + 7) / 8;
 /* If we have ocets then we have a destination and netmask */
 if (ocets > 0) {
			memcpy(&rt->dest.s_addr, p, ocets);
			p += ocets;
			rt->net.s_addr = htonl(~0U << (32 - cidr));
 }

 /* Finally, snag the router */
		memcpy(&rt->gate.s_addr, p, 4);
		p += 4;
 }
 return routes;
}
