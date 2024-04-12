static int qib_get_base_info(struct file *fp, void __user *ubase,
			     size_t ubase_size)
{
	struct qib_ctxtdata *rcd = ctxt_fp(fp);
	int ret = 0;
	struct qib_base_info *kinfo = NULL;
	struct qib_devdata *dd = rcd->dd;
	struct qib_pportdata *ppd = rcd->ppd;
	unsigned subctxt_cnt;
	int shared, master;
	size_t sz;

	subctxt_cnt = rcd->subctxt_cnt;
	if (!subctxt_cnt) {
		shared = 0;
		master = 0;
		subctxt_cnt = 1;
	} else {
		shared = 1;
		master = !subctxt_fp(fp);
	}

	sz = sizeof(*kinfo);
	/* If context sharing is not requested, allow the old size structure */
	if (!shared)
		sz -= 7 * sizeof(u64);
	if (ubase_size < sz) {
		ret = -EINVAL;
		goto bail;
	}

	kinfo = kzalloc(sizeof(*kinfo), GFP_KERNEL);
	if (kinfo == NULL) {
		ret = -ENOMEM;
		goto bail;
	}

	ret = dd->f_get_base_info(rcd, kinfo);
	if (ret < 0)
		goto bail;

	kinfo->spi_rcvhdr_cnt = dd->rcvhdrcnt;
	kinfo->spi_rcvhdrent_size = dd->rcvhdrentsize;
	kinfo->spi_tidegrcnt = rcd->rcvegrcnt;
	kinfo->spi_rcv_egrbufsize = dd->rcvegrbufsize;
	/*
	 * have to mmap whole thing
	 */
	kinfo->spi_rcv_egrbuftotlen =
		rcd->rcvegrbuf_chunks * rcd->rcvegrbuf_size;
	kinfo->spi_rcv_egrperchunk = rcd->rcvegrbufs_perchunk;
	kinfo->spi_rcv_egrchunksize = kinfo->spi_rcv_egrbuftotlen /
		rcd->rcvegrbuf_chunks;
	kinfo->spi_tidcnt = dd->rcvtidcnt / subctxt_cnt;
	if (master)
		kinfo->spi_tidcnt += dd->rcvtidcnt % subctxt_cnt;
	/*
	 * for this use, may be cfgctxts summed over all chips that
	 * are are configured and present
	 */
	kinfo->spi_nctxts = dd->cfgctxts;
	/* unit (chip/board) our context is on */
	kinfo->spi_unit = dd->unit;
	kinfo->spi_port = ppd->port;
	/* for now, only a single page */
	kinfo->spi_tid_maxsize = PAGE_SIZE;

	/*
	 * Doing this per context, and based on the skip value, etc.  This has
	 * to be the actual buffer size, since the protocol code treats it
	 * as an array.
	 *
	 * These have to be set to user addresses in the user code via mmap.
	 * These values are used on return to user code for the mmap target
	 * addresses only.  For 32 bit, same 44 bit address problem, so use
	 * the physical address, not virtual.  Before 2.6.11, using the
	 * page_address() macro worked, but in 2.6.11, even that returns the
	 * full 64 bit address (upper bits all 1's).  So far, using the
	 * physical addresses (or chip offsets, for chip mapping) works, but
	 * no doubt some future kernel release will change that, and we'll be
	 * on to yet another method of dealing with this.
	 * Normally only one of rcvhdr_tailaddr or rhf_offset is useful
	 * since the chips with non-zero rhf_offset don't normally
	 * enable tail register updates to host memory, but for testing,
	 * both can be enabled and used.
	 */
	kinfo->spi_rcvhdr_base = (u64) rcd->rcvhdrq_phys;
	kinfo->spi_rcvhdr_tailaddr = (u64) rcd->rcvhdrqtailaddr_phys;
	kinfo->spi_rhf_offset = dd->rhf_offset;
	kinfo->spi_rcv_egrbufs = (u64) rcd->rcvegr_phys;
	kinfo->spi_pioavailaddr = (u64) dd->pioavailregs_phys;
	/* setup per-unit (not port) status area for user programs */
	kinfo->spi_status = (u64) kinfo->spi_pioavailaddr +
		(char *) ppd->statusp -
		(char *) dd->pioavailregs_dma;
	kinfo->spi_uregbase = (u64) dd->uregbase + dd->ureg_align * rcd->ctxt;
	if (!shared) {
		kinfo->spi_piocnt = rcd->piocnt;
		kinfo->spi_piobufbase = (u64) rcd->piobufs;
		kinfo->spi_sendbuf_status = cvt_kvaddr(rcd->user_event_mask);
	} else if (master) {
		kinfo->spi_piocnt = (rcd->piocnt / subctxt_cnt) +
				    (rcd->piocnt % subctxt_cnt);
		/* Master's PIO buffers are after all the slave's */
		kinfo->spi_piobufbase = (u64) rcd->piobufs +
			dd->palign *
			(rcd->piocnt - kinfo->spi_piocnt);
	} else {
		unsigned slave = subctxt_fp(fp) - 1;

		kinfo->spi_piocnt = rcd->piocnt / subctxt_cnt;
		kinfo->spi_piobufbase = (u64) rcd->piobufs +
			dd->palign * kinfo->spi_piocnt * slave;
	}

	if (shared) {
		kinfo->spi_sendbuf_status =
			cvt_kvaddr(&rcd->user_event_mask[subctxt_fp(fp)]);
		/* only spi_subctxt_* fields should be set in this block! */
		kinfo->spi_subctxt_uregbase = cvt_kvaddr(rcd->subctxt_uregbase);

		kinfo->spi_subctxt_rcvegrbuf =
			cvt_kvaddr(rcd->subctxt_rcvegrbuf);
		kinfo->spi_subctxt_rcvhdr_base =
			cvt_kvaddr(rcd->subctxt_rcvhdr_base);
	}

	/*
	 * All user buffers are 2KB buffers.  If we ever support
	 * giving 4KB buffers to user processes, this will need some
	 * work.  Can't use piobufbase directly, because it has
	 * both 2K and 4K buffer base values.
	 */
	kinfo->spi_pioindex = (kinfo->spi_piobufbase - dd->pio2k_bufbase) /
		dd->palign;
	kinfo->spi_pioalign = dd->palign;
	kinfo->spi_qpair = QIB_KD_QP;
	/*
	 * user mode PIO buffers are always 2KB, even when 4KB can
	 * be received, and sent via the kernel; this is ibmaxlen
	 * for 2K MTU.
	 */
	kinfo->spi_piosize = dd->piosize2k - 2 * sizeof(u32);
	kinfo->spi_mtu = ppd->ibmaxlen; /* maxlen, not ibmtu */
	kinfo->spi_ctxt = rcd->ctxt;
	kinfo->spi_subctxt = subctxt_fp(fp);
	kinfo->spi_sw_version = QIB_KERN_SWVERSION;
	kinfo->spi_sw_version |= 1U << 31; /* QLogic-built, not kernel.org */
	kinfo->spi_hw_version = dd->revision;

	if (master)
		kinfo->spi_runtime_flags |= QIB_RUNTIME_MASTER;

	sz = (ubase_size < sizeof(*kinfo)) ? ubase_size : sizeof(*kinfo);
	if (copy_to_user(ubase, kinfo, sz))
		ret = -EFAULT;
bail:
	kfree(kinfo);
	return ret;
}
