static int writeWepKeyRid(struct airo_info *ai, WepKeyRid *wkr, int perm, int lock)
{
	int rc;
	rc = PC4500_writerid(ai, RID_WEP_TEMP, wkr, sizeof(*wkr), lock);
	if (rc!=SUCCESS)
		airo_print_err(ai->dev->name, "WEP_TEMP set %x", rc);
	if (perm) {
		rc = PC4500_writerid(ai, RID_WEP_PERM, wkr, sizeof(*wkr), lock);
		if (rc!=SUCCESS)
			airo_print_err(ai->dev->name, "WEP_PERM set %x", rc);
	}
	return rc;
}
