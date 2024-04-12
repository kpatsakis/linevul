static int pf_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct pf_unit *pf = bdev->bd_disk->private_data;
	sector_t capacity = get_capacity(pf->disk);

	if (capacity < PF_FD_MAX) {
		geo->cylinders = sector_div(capacity, PF_FD_HDS * PF_FD_SPT);
		geo->heads = PF_FD_HDS;
		geo->sectors = PF_FD_SPT;
	} else {
		geo->cylinders = sector_div(capacity, PF_HD_HDS * PF_HD_SPT);
		geo->heads = PF_HD_HDS;
		geo->sectors = PF_HD_SPT;
	}

	return 0;
}
