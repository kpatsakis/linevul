static int read_eprom_word(pegasus_t *pegasus, __u8 index, __u16 *retdata)
{
	int i;
	__u8 tmp;
	__le16 retdatai;
	int ret;

	set_register(pegasus, EpromCtrl, 0);
	set_register(pegasus, EpromOffset, index);
	set_register(pegasus, EpromCtrl, EPROM_READ);

	for (i = 0; i < REG_TIMEOUT; i++) {
		ret = get_registers(pegasus, EpromCtrl, 1, &tmp);
		if (tmp & EPROM_DONE)
			break;
		if (ret == -ESHUTDOWN)
			goto fail;
	}
	if (i >= REG_TIMEOUT)
		goto fail;

	ret = get_registers(pegasus, EpromData, 2, &retdatai);
	*retdata = le16_to_cpu(retdatai);
	return ret;

fail:
	netif_warn(pegasus, drv, pegasus->net, "%s failed\n", __func__);
	return -ETIMEDOUT;
}
