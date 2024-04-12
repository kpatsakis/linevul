static void abort_arp_failure(struct t3cdev *dev, struct sk_buff *skb)
{
	struct cpl_abort_req *req = cplhdr(skb);

	PDBG("%s t3cdev %p\n", __func__, dev);
	req->cmd = CPL_ABORT_NO_RST;
	iwch_cxgb3_ofld_send(dev, skb);
}
