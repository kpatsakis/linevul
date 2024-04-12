static void prb_fill_vlan_info(struct tpacket_kbdq_core *pkc,
			struct tpacket3_hdr *ppd)
{
	if (vlan_tx_tag_present(pkc->skb)) {
		ppd->hv1.tp_vlan_tci = vlan_tx_tag_get(pkc->skb);
		ppd->tp_status = TP_STATUS_VLAN_VALID;
	} else {
		ppd->hv1.tp_vlan_tci = 0;
		ppd->tp_status = TP_STATUS_AVAILABLE;
	}
}
