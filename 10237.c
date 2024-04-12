static int init_subctxts(struct qib_devdata *dd,
			 struct qib_ctxtdata *rcd,
			 const struct qib_user_info *uinfo)
{
	int ret = 0;
	unsigned num_subctxts;
	size_t size;

	/*
	 * If the user is requesting zero subctxts,
	 * skip the subctxt allocation.
	 */
	if (uinfo->spu_subctxt_cnt <= 0)
		goto bail;
	num_subctxts = uinfo->spu_subctxt_cnt;

	/* Check for subctxt compatibility */
	if (!qib_compatible_subctxts(uinfo->spu_userversion >> 16,
		uinfo->spu_userversion & 0xffff)) {
		qib_devinfo(dd->pcidev,
			 "Mismatched user version (%d.%d) and driver version (%d.%d) while context sharing. Ensure that driver and library are from the same release.\n",
			 (int) (uinfo->spu_userversion >> 16),
			 (int) (uinfo->spu_userversion & 0xffff),
			 QIB_USER_SWMAJOR, QIB_USER_SWMINOR);
		goto bail;
	}
	if (num_subctxts > QLOGIC_IB_MAX_SUBCTXT) {
		ret = -EINVAL;
		goto bail;
	}

	rcd->subctxt_uregbase = vmalloc_user(PAGE_SIZE * num_subctxts);
	if (!rcd->subctxt_uregbase) {
		ret = -ENOMEM;
		goto bail;
	}
	/* Note: rcd->rcvhdrq_size isn't initialized yet. */
	size = ALIGN(dd->rcvhdrcnt * dd->rcvhdrentsize *
		     sizeof(u32), PAGE_SIZE) * num_subctxts;
	rcd->subctxt_rcvhdr_base = vmalloc_user(size);
	if (!rcd->subctxt_rcvhdr_base) {
		ret = -ENOMEM;
		goto bail_ureg;
	}

	rcd->subctxt_rcvegrbuf = vmalloc_user(rcd->rcvegrbuf_chunks *
					      rcd->rcvegrbuf_size *
					      num_subctxts);
	if (!rcd->subctxt_rcvegrbuf) {
		ret = -ENOMEM;
		goto bail_rhdr;
	}

	rcd->subctxt_cnt = uinfo->spu_subctxt_cnt;
	rcd->subctxt_id = uinfo->spu_subctxt_id;
	rcd->active_slaves = 1;
	rcd->redirect_seq_cnt = 1;
	set_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag);
	goto bail;

bail_rhdr:
	vfree(rcd->subctxt_rcvhdr_base);
bail_ureg:
	vfree(rcd->subctxt_uregbase);
	rcd->subctxt_uregbase = NULL;
bail:
	return ret;
}
