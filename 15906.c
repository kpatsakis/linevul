int hns_ppe_init(struct dsaf_device *dsaf_dev)
{
	int ret;
	int i;

	for (i = 0; i < HNS_PPE_COM_NUM; i++) {
		ret = hns_ppe_common_get_cfg(dsaf_dev, i);
		if (ret)
			goto get_cfg_fail;

		ret = hns_rcb_common_get_cfg(dsaf_dev, i);
		if (ret)
			goto get_cfg_fail;

		hns_ppe_get_cfg(dsaf_dev->ppe_common[i]);

		ret = hns_rcb_get_cfg(dsaf_dev->rcb_common[i]);
		if (ret)
			goto get_cfg_fail;
	}

	for (i = 0; i < HNS_PPE_COM_NUM; i++)
		hns_ppe_reset_common(dsaf_dev, i);

	return 0;

get_cfg_fail:
	for (i = 0; i < HNS_PPE_COM_NUM; i++) {
		hns_rcb_common_free_cfg(dsaf_dev, i);
		hns_ppe_common_free_cfg(dsaf_dev, i);
	}

	return ret;
}
