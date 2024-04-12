void part_set_generic_name(const struct blk_desc *dev_desc,
	int part_num, char *name)
{
	char *devtype;

	switch (dev_desc->if_type) {
	case IF_TYPE_IDE:
	case IF_TYPE_SATA:
	case IF_TYPE_ATAPI:
		devtype = "hd";
		break;
	case IF_TYPE_SCSI:
		devtype = "sd";
		break;
	case IF_TYPE_USB:
		devtype = "usbd";
		break;
	case IF_TYPE_DOC:
		devtype = "docd";
		break;
	case IF_TYPE_MMC:
	case IF_TYPE_SD:
		devtype = "mmcsd";
		break;
	default:
		devtype = "xx";
		break;
	}

	sprintf(name, "%s%c%d", devtype, 'a' + dev_desc->devnum, part_num);
}
