static int ims_pcu_get_info(struct ims_pcu *pcu)
{
	int error;

	error = ims_pcu_execute_query(pcu, GET_INFO);
	if (error) {
		dev_err(pcu->dev,
			"GET_INFO command failed, error: %d\n", error);
		return error;
	}

	memcpy(pcu->part_number,
	       &pcu->cmd_buf[IMS_PCU_INFO_PART_OFFSET],
	       sizeof(pcu->part_number));
	memcpy(pcu->date_of_manufacturing,
	       &pcu->cmd_buf[IMS_PCU_INFO_DOM_OFFSET],
	       sizeof(pcu->date_of_manufacturing));
	memcpy(pcu->serial_number,
	       &pcu->cmd_buf[IMS_PCU_INFO_SERIAL_OFFSET],
	       sizeof(pcu->serial_number));

	return 0;
}
