static int do_ipv6_setsockopt(struct sock *sk, int level, int optname,
char __user *optval, unsigned int optlen)
{
struct ipv6_pinfo *np = inet6_sk(sk);
struct net *net = sock_net(sk);
int val, valbool;
int retv = -ENOPROTOOPT;
bool needs_rtnl = setsockopt_needs_rtnl(optname);

if (!optval)
val = 0;
else {
if (optlen >= sizeof(int)) {
if (get_user(val, (int __user *) optval))
return -EFAULT;
} else
val = 0;
}

valbool = (val != 0);

if (ip6_mroute_opt(optname))
return ip6_mroute_setsockopt(sk, optname, optval, optlen);

if (needs_rtnl)
rtnl_lock();
lock_sock(sk);

switch (optname) {

case IPV6_ADDRFORM:
if (optlen < sizeof(int))
goto e_inval;
if (val == PF_INET) {
struct ipv6_txoptions *opt;
struct sk_buff *pktopt;

if (sk->sk_type == SOCK_RAW)
break;

if (sk->sk_protocol == IPPROTO_UDP ||
sk->sk_protocol == IPPROTO_UDPLITE) {
struct udp_sock *up = udp_sk(sk);
if (up->pending == AF_INET6) {
retv = -EBUSY;
break;
}
} else if (sk->sk_protocol != IPPROTO_TCP)
break;

if (sk->sk_state != TCP_ESTABLISHED) {
retv = -ENOTCONN;
break;
}

if (ipv6_only_sock(sk) ||
!ipv6_addr_v4mapped(&sk->sk_v6_daddr)) {
retv = -EADDRNOTAVAIL;
break;
}

fl6_free_socklist(sk);
ipv6_sock_mc_close(sk);

/*
* Sock is moving from IPv6 to IPv4 (sk_prot), so
* remove it from the refcnt debug socks count in the
* original family...
*/
sk_refcnt_debug_dec(sk);

if (sk->sk_protocol == IPPROTO_TCP) {
struct inet_connection_sock *icsk = inet_csk(sk);
local_bh_disable();
sock_prot_inuse_add(net, sk->sk_prot, -1);
sock_prot_inuse_add(net, &tcp_prot, 1);
local_bh_enable();
sk->sk_prot = &tcp_prot;
icsk->icsk_af_ops = &ipv4_specific;
sk->sk_socket->ops = &inet_stream_ops;
sk->sk_family = PF_INET;
tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
} else {
struct proto *prot = &udp_prot;

if (sk->sk_protocol == IPPROTO_UDPLITE)
prot = &udplite_prot;
local_bh_disable();
sock_prot_inuse_add(net, sk->sk_prot, -1);
sock_prot_inuse_add(net, prot, 1);
local_bh_enable();
sk->sk_prot = prot;
sk->sk_socket->ops = &inet_dgram_ops;
sk->sk_family = PF_INET;
}
			opt = xchg(&np->opt, NULL);
			if (opt)
				sock_kfree_s(sk, opt, opt->tot_len);
pktopt = xchg(&np->pktoptions, NULL);
kfree_skb(pktopt);

sk->sk_destruct = inet_sock_destruct;
/*
* ... and add it to the refcnt debug socks count
* in the new family. -acme
*/
sk_refcnt_debug_inc(sk);
module_put(THIS_MODULE);
retv = 0;
break;
}
goto e_inval;

case IPV6_V6ONLY:
if (optlen < sizeof(int) ||
inet_sk(sk)->inet_num)
goto e_inval;
sk->sk_ipv6only = valbool;
retv = 0;
break;

case IPV6_RECVPKTINFO:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxinfo = valbool;
retv = 0;
break;

case IPV6_2292PKTINFO:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxoinfo = valbool;
retv = 0;
break;

case IPV6_RECVHOPLIMIT:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxhlim = valbool;
retv = 0;
break;

case IPV6_2292HOPLIMIT:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxohlim = valbool;
retv = 0;
break;

case IPV6_RECVRTHDR:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.srcrt = valbool;
retv = 0;
break;

case IPV6_2292RTHDR:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.osrcrt = valbool;
retv = 0;
break;

case IPV6_RECVHOPOPTS:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.hopopts = valbool;
retv = 0;
break;

case IPV6_2292HOPOPTS:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.ohopopts = valbool;
retv = 0;
break;

case IPV6_RECVDSTOPTS:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.dstopts = valbool;
retv = 0;
break;

case IPV6_2292DSTOPTS:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.odstopts = valbool;
retv = 0;
break;

case IPV6_TCLASS:
if (optlen < sizeof(int))
goto e_inval;
if (val < -1 || val > 0xff)
goto e_inval;
/* RFC 3542, 6.5: default traffic class of 0x0 */
if (val == -1)
val = 0;
np->tclass = val;
retv = 0;
break;

case IPV6_RECVTCLASS:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxtclass = valbool;
retv = 0;
break;

case IPV6_FLOWINFO:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxflow = valbool;
retv = 0;
break;

case IPV6_RECVPATHMTU:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxpmtu = valbool;
retv = 0;
break;

case IPV6_TRANSPARENT:
if (valbool && !ns_capable(net->user_ns, CAP_NET_ADMIN) &&
!ns_capable(net->user_ns, CAP_NET_RAW)) {
retv = -EPERM;
break;
}
if (optlen < sizeof(int))
goto e_inval;
/* we don't have a separate transparent bit for IPV6 we use the one in the IPv4 socket */
inet_sk(sk)->transparent = valbool;
retv = 0;
break;

case IPV6_RECVORIGDSTADDR:
if (optlen < sizeof(int))
goto e_inval;
np->rxopt.bits.rxorigdstaddr = valbool;
retv = 0;
break;

case IPV6_HOPOPTS:
case IPV6_RTHDRDSTOPTS:
case IPV6_RTHDR:
case IPV6_DSTOPTS:
{
struct ipv6_txoptions *opt;

/* remove any sticky options header with a zero option
* length, per RFC3542.
*/
if (optlen == 0)
optval = NULL;
else if (!optval)
goto e_inval;
else if (optlen < sizeof(struct ipv6_opt_hdr) ||
optlen & 0x7 || optlen > 8 * 255)
goto e_inval;

/* hop-by-hop / destination options are privileged option */
retv = -EPERM;
if (optname != IPV6_RTHDR && !ns_capable(net->user_ns, CAP_NET_RAW))
break;

		opt = ipv6_renew_options(sk, np->opt, optname,
(struct ipv6_opt_hdr __user *)optval,
optlen);
if (IS_ERR(opt)) {
retv = PTR_ERR(opt);
break;
}

/* routing header option needs extra check */
retv = -EINVAL;
if (optname == IPV6_RTHDR && opt && opt->srcrt) {
struct ipv6_rt_hdr *rthdr = opt->srcrt;
switch (rthdr->type) {
#if IS_ENABLED(CONFIG_IPV6_MIP6)
case IPV6_SRCRT_TYPE_2:
if (rthdr->hdrlen != 2 ||
rthdr->segments_left != 1)
goto sticky_done;

break;
#endif
default:
goto sticky_done;
}
}

retv = 0;
opt = ipv6_update_options(sk, opt);
sticky_done:
		if (opt)
			sock_kfree_s(sk, opt, opt->tot_len);
break;
}

case IPV6_PKTINFO:
{
struct in6_pktinfo pkt;

if (optlen == 0)
goto e_inval;
else if (optlen < sizeof(struct in6_pktinfo) || !optval)
goto e_inval;

if (copy_from_user(&pkt, optval, sizeof(struct in6_pktinfo))) {
retv = -EFAULT;
break;
}
if (sk->sk_bound_dev_if && pkt.ipi6_ifindex != sk->sk_bound_dev_if)
goto e_inval;

np->sticky_pktinfo.ipi6_ifindex = pkt.ipi6_ifindex;
np->sticky_pktinfo.ipi6_addr = pkt.ipi6_addr;
retv = 0;
break;
}

case IPV6_2292PKTOPTIONS:
{
struct ipv6_txoptions *opt = NULL;
struct msghdr msg;
struct flowi6 fl6;
int junk;

memset(&fl6, 0, sizeof(fl6));
fl6.flowi6_oif = sk->sk_bound_dev_if;
fl6.flowi6_mark = sk->sk_mark;

if (optlen == 0)
goto update;

/* 1K is probably excessive
* 1K is surely not enough, 2K per standard header is 16K.
*/
retv = -EINVAL;
if (optlen > 64*1024)
break;

opt = sock_kmalloc(sk, sizeof(*opt) + optlen, GFP_KERNEL);
retv = -ENOBUFS;
if (!opt)
break;

memset(opt, 0, sizeof(*opt));
opt->tot_len = sizeof(*opt) + optlen;
retv = -EFAULT;
if (copy_from_user(opt+1, optval, optlen))
goto done;

msg.msg_controllen = optlen;
msg.msg_control = (void *)(opt+1);

retv = ip6_datagram_send_ctl(net, sk, &msg, &fl6, opt, &junk,
&junk, &junk);
if (retv)
goto done;
update:
retv = 0;
opt = ipv6_update_options(sk, opt);
done:
		if (opt)
			sock_kfree_s(sk, opt, opt->tot_len);
break;
}
case IPV6_UNICAST_HOPS:
if (optlen < sizeof(int))
goto e_inval;
if (val > 255 || val < -1)
goto e_inval;
np->hop_limit = val;
retv = 0;
break;

case IPV6_MULTICAST_HOPS:
if (sk->sk_type == SOCK_STREAM)
break;
if (optlen < sizeof(int))
goto e_inval;
if (val > 255 || val < -1)
goto e_inval;
np->mcast_hops = (val == -1 ? IPV6_DEFAULT_MCASTHOPS : val);
retv = 0;
break;

case IPV6_MULTICAST_LOOP:
if (optlen < sizeof(int))
goto e_inval;
if (val != valbool)
goto e_inval;
np->mc_loop = valbool;
retv = 0;
break;

case IPV6_UNICAST_IF:
{
struct net_device *dev = NULL;
int ifindex;

if (optlen != sizeof(int))
goto e_inval;

ifindex = (__force int)ntohl((__force __be32)val);
if (ifindex == 0) {
np->ucast_oif = 0;
retv = 0;
break;
}

dev = dev_get_by_index(net, ifindex);
retv = -EADDRNOTAVAIL;
if (!dev)
break;
dev_put(dev);

retv = -EINVAL;
if (sk->sk_bound_dev_if)
break;

np->ucast_oif = ifindex;
retv = 0;
break;
}

case IPV6_MULTICAST_IF:
if (sk->sk_type == SOCK_STREAM)
break;
if (optlen < sizeof(int))
goto e_inval;

if (val) {
struct net_device *dev;

if (sk->sk_bound_dev_if && sk->sk_bound_dev_if != val)
goto e_inval;

dev = dev_get_by_index(net, val);
if (!dev) {
retv = -ENODEV;
break;
}
dev_put(dev);
}
np->mcast_oif = val;
retv = 0;
break;
case IPV6_ADD_MEMBERSHIP:
case IPV6_DROP_MEMBERSHIP:
{
struct ipv6_mreq mreq;

if (optlen < sizeof(struct ipv6_mreq))
goto e_inval;

retv = -EPROTO;
if (inet_sk(sk)->is_icsk)
break;

retv = -EFAULT;
if (copy_from_user(&mreq, optval, sizeof(struct ipv6_mreq)))
break;

if (optname == IPV6_ADD_MEMBERSHIP)
retv = ipv6_sock_mc_join(sk, mreq.ipv6mr_ifindex, &mreq.ipv6mr_multiaddr);
else
retv = ipv6_sock_mc_drop(sk, mreq.ipv6mr_ifindex, &mreq.ipv6mr_multiaddr);
break;
}
case IPV6_JOIN_ANYCAST:
case IPV6_LEAVE_ANYCAST:
{
struct ipv6_mreq mreq;

if (optlen < sizeof(struct ipv6_mreq))
goto e_inval;

retv = -EFAULT;
if (copy_from_user(&mreq, optval, sizeof(struct ipv6_mreq)))
break;

if (optname == IPV6_JOIN_ANYCAST)
retv = ipv6_sock_ac_join(sk, mreq.ipv6mr_ifindex, &mreq.ipv6mr_acaddr);
else
retv = ipv6_sock_ac_drop(sk, mreq.ipv6mr_ifindex, &mreq.ipv6mr_acaddr);
break;
}
case MCAST_JOIN_GROUP:
case MCAST_LEAVE_GROUP:
{
struct group_req greq;
struct sockaddr_in6 *psin6;

if (optlen < sizeof(struct group_req))
goto e_inval;

retv = -EFAULT;
if (copy_from_user(&greq, optval, sizeof(struct group_req)))
break;
if (greq.gr_group.ss_family != AF_INET6) {
retv = -EADDRNOTAVAIL;
break;
}
psin6 = (struct sockaddr_in6 *)&greq.gr_group;
if (optname == MCAST_JOIN_GROUP)
retv = ipv6_sock_mc_join(sk, greq.gr_interface,
&psin6->sin6_addr);
else
retv = ipv6_sock_mc_drop(sk, greq.gr_interface,
&psin6->sin6_addr);
break;
}
case MCAST_JOIN_SOURCE_GROUP:
case MCAST_LEAVE_SOURCE_GROUP:
case MCAST_BLOCK_SOURCE:
case MCAST_UNBLOCK_SOURCE:
{
struct group_source_req greqs;
int omode, add;

if (optlen < sizeof(struct group_source_req))
goto e_inval;
if (copy_from_user(&greqs, optval, sizeof(greqs))) {
retv = -EFAULT;
break;
}
if (greqs.gsr_group.ss_family != AF_INET6 ||
greqs.gsr_source.ss_family != AF_INET6) {
retv = -EADDRNOTAVAIL;
break;
}
if (optname == MCAST_BLOCK_SOURCE) {
omode = MCAST_EXCLUDE;
add = 1;
} else if (optname == MCAST_UNBLOCK_SOURCE) {
omode = MCAST_EXCLUDE;
add = 0;
} else if (optname == MCAST_JOIN_SOURCE_GROUP) {
struct sockaddr_in6 *psin6;

psin6 = (struct sockaddr_in6 *)&greqs.gsr_group;
retv = ipv6_sock_mc_join(sk, greqs.gsr_interface,
&psin6->sin6_addr);
/* prior join w/ different source is ok */
if (retv && retv != -EADDRINUSE)
break;
omode = MCAST_INCLUDE;
add = 1;
} else /* MCAST_LEAVE_SOURCE_GROUP */ {
omode = MCAST_INCLUDE;
add = 0;
}
retv = ip6_mc_source(add, omode, sk, &greqs);
break;
}
case MCAST_MSFILTER:
{
struct group_filter *gsf;

if (optlen < GROUP_FILTER_SIZE(0))
goto e_inval;
if (optlen > sysctl_optmem_max) {
retv = -ENOBUFS;
break;
}
gsf = kmalloc(optlen, GFP_KERNEL);
if (!gsf) {
retv = -ENOBUFS;
break;
}
retv = -EFAULT;
if (copy_from_user(gsf, optval, optlen)) {
kfree(gsf);
break;
}
/* numsrc >= (4G-140)/128 overflow in 32 bits */
if (gsf->gf_numsrc >= 0x1ffffffU ||
gsf->gf_numsrc > sysctl_mld_max_msf) {
kfree(gsf);
retv = -ENOBUFS;
break;
}
if (GROUP_FILTER_SIZE(gsf->gf_numsrc) > optlen) {
kfree(gsf);
retv = -EINVAL;
break;
}
retv = ip6_mc_msfilter(sk, gsf);
kfree(gsf);

break;
}
case IPV6_ROUTER_ALERT:
if (optlen < sizeof(int))
goto e_inval;
retv = ip6_ra_control(sk, val);
break;
case IPV6_MTU_DISCOVER:
if (optlen < sizeof(int))
goto e_inval;
if (val < IPV6_PMTUDISC_DONT || val > IPV6_PMTUDISC_OMIT)
goto e_inval;
np->pmtudisc = val;
retv = 0;
break;
case IPV6_MTU:
if (optlen < sizeof(int))
goto e_inval;
if (val && val < IPV6_MIN_MTU)
goto e_inval;
np->frag_size = val;
retv = 0;
break;
case IPV6_RECVERR:
if (optlen < sizeof(int))
goto e_inval;
np->recverr = valbool;
if (!val)
skb_queue_purge(&sk->sk_error_queue);
retv = 0;
break;
case IPV6_FLOWINFO_SEND:
if (optlen < sizeof(int))
goto e_inval;
np->sndflow = valbool;
retv = 0;
break;
case IPV6_FLOWLABEL_MGR:
retv = ipv6_flowlabel_opt(sk, optval, optlen);
break;
case IPV6_IPSEC_POLICY:
case IPV6_XFRM_POLICY:
retv = -EPERM;
if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
break;
retv = xfrm_user_policy(sk, optname, optval, optlen);
break;

case IPV6_ADDR_PREFERENCES:
{
unsigned int pref = 0;
unsigned int prefmask = ~0;

if (optlen < sizeof(int))
goto e_inval;

retv = -EINVAL;

/* check PUBLIC/TMP/PUBTMP_DEFAULT conflicts */
switch (val & (IPV6_PREFER_SRC_PUBLIC|
IPV6_PREFER_SRC_TMP|
IPV6_PREFER_SRC_PUBTMP_DEFAULT)) {
case IPV6_PREFER_SRC_PUBLIC:
pref |= IPV6_PREFER_SRC_PUBLIC;
break;
case IPV6_PREFER_SRC_TMP:
pref |= IPV6_PREFER_SRC_TMP;
break;
case IPV6_PREFER_SRC_PUBTMP_DEFAULT:
break;
case 0:
goto pref_skip_pubtmp;
default:
goto e_inval;
}

prefmask &= ~(IPV6_PREFER_SRC_PUBLIC|
IPV6_PREFER_SRC_TMP);
pref_skip_pubtmp:

/* check HOME/COA conflicts */
switch (val & (IPV6_PREFER_SRC_HOME|IPV6_PREFER_SRC_COA)) {
case IPV6_PREFER_SRC_HOME:
break;
case IPV6_PREFER_SRC_COA:
pref |= IPV6_PREFER_SRC_COA;
case 0:
goto pref_skip_coa;
default:
goto e_inval;
}

prefmask &= ~IPV6_PREFER_SRC_COA;
pref_skip_coa:

/* check CGA/NONCGA conflicts */
switch (val & (IPV6_PREFER_SRC_CGA|IPV6_PREFER_SRC_NONCGA)) {
case IPV6_PREFER_SRC_CGA:
case IPV6_PREFER_SRC_NONCGA:
case 0:
break;
default:
goto e_inval;
}

np->srcprefs = (np->srcprefs & prefmask) | pref;
retv = 0;

break;
}
case IPV6_MINHOPCOUNT:
if (optlen < sizeof(int))
goto e_inval;
if (val < 0 || val > 255)
goto e_inval;
np->min_hopcount = val;
retv = 0;
break;
case IPV6_DONTFRAG:
np->dontfrag = valbool;
retv = 0;
break;
case IPV6_AUTOFLOWLABEL:
np->autoflowlabel = valbool;
retv = 0;
break;
}

release_sock(sk);
if (needs_rtnl)
rtnl_unlock();

return retv;

e_inval:
release_sock(sk);
if (needs_rtnl)
rtnl_unlock();
return -EINVAL;
}
