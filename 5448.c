static int ap_queue_enable_interruption(ap_qid_t qid, void *ind)
{
#ifdef CONFIG_64BIT
	struct ap_queue_status status;
	int t_depth, t_device_type, rc, i;

	rc = -EBUSY;
	status = ap_queue_interruption_control(qid, ind);

	for (i = 0; i < AP_MAX_RESET; i++) {
		switch (status.response_code) {
		case AP_RESPONSE_NORMAL:
			if (status.int_enabled)
				return 0;
			break;
		case AP_RESPONSE_RESET_IN_PROGRESS:
		case AP_RESPONSE_BUSY:
			if (i < AP_MAX_RESET - 1) {
				udelay(5);
				status = ap_queue_interruption_control(qid,
								       ind);
				continue;
			}
			break;
		case AP_RESPONSE_Q_NOT_AVAIL:
		case AP_RESPONSE_DECONFIGURED:
		case AP_RESPONSE_CHECKSTOPPED:
		case AP_RESPONSE_INVALID_ADDRESS:
			return -ENODEV;
		case AP_RESPONSE_OTHERWISE_CHANGED:
			if (status.int_enabled)
				return 0;
			break;
		default:
			break;
		}
		if (i < AP_MAX_RESET - 1) {
			udelay(5);
			status = ap_test_queue(qid, &t_depth, &t_device_type);
		}
	}
	return rc;
#else
	return -EINVAL;
#endif
}
