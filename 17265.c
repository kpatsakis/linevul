static void svc_rdma_send_wc_common(struct svcxprt_rdma *xprt,
				    struct ib_wc *wc,
				    const char *opname)
{
	if (wc->status != IB_WC_SUCCESS)
		goto err;

out:
	atomic_inc(&xprt->sc_sq_avail);
	wake_up(&xprt->sc_send_wait);
	return;

err:
	set_bit(XPT_CLOSE, &xprt->sc_xprt.xpt_flags);
	if (wc->status != IB_WC_WR_FLUSH_ERR)
		pr_err("svcrdma: %s: %s (%u/0x%x)\n",
		       opname, ib_wc_status_msg(wc->status),
		       wc->status, wc->vendor_err);
	goto out;
}
