static int pcd_drive_status(struct cdrom_device_info *cdi, int slot_nr)
{
	char rc_cmd[12] = { 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	struct pcd_unit *cd = cdi->handle;

	if (pcd_ready_wait(cd, PCD_READY_TMO))
		return CDS_DRIVE_NOT_READY;
	if (pcd_atapi(cd, rc_cmd, 8, pcd_scratch, DBMSG("check media")))
		return CDS_NO_DISC;
	return CDS_DISC_OK;
}
