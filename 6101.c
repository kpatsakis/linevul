static int scsi_disk_initfn(SCSIDevice *dev)
{
    DriveInfo *dinfo;
    uint8_t scsi_type;

    if (!dev->conf.bs) {
        scsi_type = TYPE_DISK;  /* will die in scsi_initfn() */
    } else {
        dinfo = drive_get_by_blockdev(dev->conf.bs);
        scsi_type = dinfo->media_cd ? TYPE_ROM : TYPE_DISK;
    }

    return scsi_initfn(dev, scsi_type);
}
