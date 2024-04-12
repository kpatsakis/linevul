static int do_qib_user_sdma_queue_create(struct file *fp)
{
	struct qib_filedata *fd = fp->private_data;
	struct qib_ctxtdata *rcd = fd->rcd;
	struct qib_devdata *dd = rcd->dd;

	if (dd->flags & QIB_HAS_SEND_DMA) {

		fd->pq = qib_user_sdma_queue_create(&dd->pcidev->dev,
						    dd->unit,
						    rcd->ctxt,
						    fd->subctxt);
		if (!fd->pq)
			return -ENOMEM;
	}

	return 0;
}
