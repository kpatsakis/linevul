static inline int arp_packet_match(const struct arphdr *arphdr,
				   struct net_device *dev,
				   const char *indev,
				   const char *outdev,
				   const struct arpt_arp *arpinfo)
{
	const char *arpptr = (char *)(arphdr + 1);
	const char *src_devaddr, *tgt_devaddr;
	__be32 src_ipaddr, tgt_ipaddr;
	long ret;

#define FWINV(bool, invflg) ((bool) ^ !!(arpinfo->invflags & (invflg)))

	if (FWINV((arphdr->ar_op & arpinfo->arpop_mask) != arpinfo->arpop,
		  ARPT_INV_ARPOP)) {
		dprintf("ARP operation field mismatch.\n");
		dprintf("ar_op: %04x info->arpop: %04x info->arpop_mask: %04x\n",
			arphdr->ar_op, arpinfo->arpop, arpinfo->arpop_mask);
		return 0;
	}

	if (FWINV((arphdr->ar_hrd & arpinfo->arhrd_mask) != arpinfo->arhrd,
		  ARPT_INV_ARPHRD)) {
		dprintf("ARP hardware address format mismatch.\n");
		dprintf("ar_hrd: %04x info->arhrd: %04x info->arhrd_mask: %04x\n",
			arphdr->ar_hrd, arpinfo->arhrd, arpinfo->arhrd_mask);
		return 0;
	}

	if (FWINV((arphdr->ar_pro & arpinfo->arpro_mask) != arpinfo->arpro,
		  ARPT_INV_ARPPRO)) {
		dprintf("ARP protocol address format mismatch.\n");
		dprintf("ar_pro: %04x info->arpro: %04x info->arpro_mask: %04x\n",
			arphdr->ar_pro, arpinfo->arpro, arpinfo->arpro_mask);
		return 0;
	}

	if (FWINV((arphdr->ar_hln & arpinfo->arhln_mask) != arpinfo->arhln,
		  ARPT_INV_ARPHLN)) {
		dprintf("ARP hardware address length mismatch.\n");
		dprintf("ar_hln: %02x info->arhln: %02x info->arhln_mask: %02x\n",
			arphdr->ar_hln, arpinfo->arhln, arpinfo->arhln_mask);
		return 0;
	}

	src_devaddr = arpptr;
	arpptr += dev->addr_len;
	memcpy(&src_ipaddr, arpptr, sizeof(u32));
	arpptr += sizeof(u32);
	tgt_devaddr = arpptr;
	arpptr += dev->addr_len;
	memcpy(&tgt_ipaddr, arpptr, sizeof(u32));

	if (FWINV(arp_devaddr_compare(&arpinfo->src_devaddr, src_devaddr, dev->addr_len),
		  ARPT_INV_SRCDEVADDR) ||
	    FWINV(arp_devaddr_compare(&arpinfo->tgt_devaddr, tgt_devaddr, dev->addr_len),
		  ARPT_INV_TGTDEVADDR)) {
		dprintf("Source or target device address mismatch.\n");

		return 0;
	}

	if (FWINV((src_ipaddr & arpinfo->smsk.s_addr) != arpinfo->src.s_addr,
		  ARPT_INV_SRCIP) ||
	    FWINV(((tgt_ipaddr & arpinfo->tmsk.s_addr) != arpinfo->tgt.s_addr),
		  ARPT_INV_TGTIP)) {
		dprintf("Source or target IP address mismatch.\n");

		dprintf("SRC: %pI4. Mask: %pI4. Target: %pI4.%s\n",
			&src_ipaddr,
			&arpinfo->smsk.s_addr,
			&arpinfo->src.s_addr,
			arpinfo->invflags & ARPT_INV_SRCIP ? " (INV)" : "");
		dprintf("TGT: %pI4 Mask: %pI4 Target: %pI4.%s\n",
			&tgt_ipaddr,
			&arpinfo->tmsk.s_addr,
			&arpinfo->tgt.s_addr,
			arpinfo->invflags & ARPT_INV_TGTIP ? " (INV)" : "");
		return 0;
	}

	/* Look for ifname matches.  */
	ret = ifname_compare(indev, arpinfo->iniface, arpinfo->iniface_mask);

	if (FWINV(ret != 0, ARPT_INV_VIA_IN)) {
		dprintf("VIA in mismatch (%s vs %s).%s\n",
			indev, arpinfo->iniface,
			arpinfo->invflags & ARPT_INV_VIA_IN ? " (INV)" : "");
		return 0;
	}

	ret = ifname_compare(outdev, arpinfo->outiface, arpinfo->outiface_mask);

	if (FWINV(ret != 0, ARPT_INV_VIA_OUT)) {
		dprintf("VIA out mismatch (%s vs %s).%s\n",
			outdev, arpinfo->outiface,
			arpinfo->invflags & ARPT_INV_VIA_OUT ? " (INV)" : "");
		return 0;
	}

	return 1;
#undef FWINV
}
