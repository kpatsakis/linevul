kernel_rx_buf_size_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned rx_buf_size;

	if (vector_size(strvec) == 2 &&
	    read_unsigned_strvec(strvec, 1, &rx_buf_size, 0, UINT_MAX, false)) {
		vrrp->kernel_rx_buf_size = rx_buf_size;
		return;
	}

	report_config_error(CONFIG_GENERAL_ERROR, "(%s) invalid kernel_rx_buf_size specified", vrrp->iname);
}
