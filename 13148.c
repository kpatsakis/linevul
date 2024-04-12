static void pf_req_sense(struct pf_unit *pf, int quiet)
{
	char rs_cmd[12] =
	    { ATAPI_REQ_SENSE, pf->lun << 5, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 };
	char buf[16];
	int r;

	r = pf_command(pf, rs_cmd, 16, "Request sense");
	mdelay(1);
	if (!r)
		pf_completion(pf, buf, "Request sense");

	if ((!r) && (!quiet))
		printk("%s: Sense key: %x, ASC: %x, ASQ: %x\n",
		       pf->name, buf[2] & 0xf, buf[12], buf[13]);
}
