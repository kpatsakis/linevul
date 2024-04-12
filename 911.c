ip_packet_match(const struct iphdr *ip,
		const char *indev,
		const char *outdev,
		const struct ipt_ip *ipinfo,
		int isfrag)
{
	unsigned long ret;

#define FWINV(bool, invflg) ((bool) ^ !!(ipinfo->invflags & (invflg)))

	if (FWINV((ip->saddr&ipinfo->smsk.s_addr) != ipinfo->src.s_addr,
		  IPT_INV_SRCIP) ||
	    FWINV((ip->daddr&ipinfo->dmsk.s_addr) != ipinfo->dst.s_addr,
		  IPT_INV_DSTIP)) {
		dprintf("Source or dest mismatch.\n");

		dprintf("SRC: %pI4. Mask: %pI4. Target: %pI4.%s\n",
			&ip->saddr, &ipinfo->smsk.s_addr, &ipinfo->src.s_addr,
			ipinfo->invflags & IPT_INV_SRCIP ? " (INV)" : "");
		dprintf("DST: %pI4 Mask: %pI4 Target: %pI4.%s\n",
			&ip->daddr, &ipinfo->dmsk.s_addr, &ipinfo->dst.s_addr,
			ipinfo->invflags & IPT_INV_DSTIP ? " (INV)" : "");
		return false;
	}

	ret = ifname_compare_aligned(indev, ipinfo->iniface, ipinfo->iniface_mask);

	if (FWINV(ret != 0, IPT_INV_VIA_IN)) {
		dprintf("VIA in mismatch (%s vs %s).%s\n",
			indev, ipinfo->iniface,
			ipinfo->invflags & IPT_INV_VIA_IN ? " (INV)" : "");
		return false;
	}

	ret = ifname_compare_aligned(outdev, ipinfo->outiface, ipinfo->outiface_mask);

	if (FWINV(ret != 0, IPT_INV_VIA_OUT)) {
		dprintf("VIA out mismatch (%s vs %s).%s\n",
			outdev, ipinfo->outiface,
			ipinfo->invflags & IPT_INV_VIA_OUT ? " (INV)" : "");
		return false;
	}

	/* Check specific protocol */
	if (ipinfo->proto &&
	    FWINV(ip->protocol != ipinfo->proto, IPT_INV_PROTO)) {
		dprintf("Packet protocol %hi does not match %hi.%s\n",
			ip->protocol, ipinfo->proto,
			ipinfo->invflags & IPT_INV_PROTO ? " (INV)" : "");
		return false;
	}

	/* If we have a fragment rule but the packet is not a fragment
	 * then we return zero */
	if (FWINV((ipinfo->flags&IPT_F_FRAG) && !isfrag, IPT_INV_FRAG)) {
		dprintf("Fragment rule but not fragment.%s\n",
			ipinfo->invflags & IPT_INV_FRAG ? " (INV)" : "");
		return false;
	}

	return true;
}
