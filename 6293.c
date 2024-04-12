static void scsi_disk_reset(DeviceState *dev)
{
    SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev.qdev, dev);
    uint64_t nb_sectors;

    scsi_device_purge_requests(&s->qdev, SENSE_CODE(RESET));

    bdrv_get_geometry(s->bs, &nb_sectors);
    nb_sectors /= s->cluster_size;
    if (nb_sectors) {
        nb_sectors--;
    }
    s->max_lba = nb_sectors;
}
