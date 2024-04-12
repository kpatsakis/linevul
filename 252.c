static int setup_ctxt(struct qib_pportdata *ppd, int ctxt,
		      struct file *fp, const struct qib_user_info *uinfo)
{
	struct qib_filedata *fd = fp->private_data;
	struct qib_devdata *dd = ppd->dd;
	struct qib_ctxtdata *rcd;
	void *ptmp = NULL;
	int ret;
	int numa_id;

	assign_ctxt_affinity(fp, dd);

	numa_id = qib_numa_aware ? ((fd->rec_cpu_num != -1) ?
		cpu_to_node(fd->rec_cpu_num) :
		numa_node_id()) : dd->assigned_node_id;

	rcd = qib_create_ctxtdata(ppd, ctxt, numa_id);

	/*
	 * Allocate memory for use in qib_tid_update() at open to
	 * reduce cost of expected send setup per message segment
	 */
	if (rcd)
		ptmp = kmalloc(dd->rcvtidcnt * sizeof(u16) +
			       dd->rcvtidcnt * sizeof(struct page **),
			       GFP_KERNEL);

	if (!rcd || !ptmp) {
		qib_dev_err(dd,
			"Unable to allocate ctxtdata memory, failing open\n");
		ret = -ENOMEM;
		goto bailerr;
	}
	rcd->userversion = uinfo->spu_userversion;
	ret = init_subctxts(dd, rcd, uinfo);
	if (ret)
		goto bailerr;
	rcd->tid_pg_list = ptmp;
	rcd->pid = current->pid;
	init_waitqueue_head(&dd->rcd[ctxt]->wait);
	strlcpy(rcd->comm, current->comm, sizeof(rcd->comm));
	ctxt_fp(fp) = rcd;
	qib_stats.sps_ctxts++;
	dd->freectxts--;
	ret = 0;
	goto bail;

bailerr:
	if (fd->rec_cpu_num != -1)
		__clear_bit(fd->rec_cpu_num, qib_cpulist);

	dd->rcd[ctxt] = NULL;
	kfree(rcd);
	kfree(ptmp);
bail:
	return ret;
}
