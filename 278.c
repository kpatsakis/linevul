static void guid_handler(struct ipmi_smi *intf, struct ipmi_recv_msg *msg)
{
	struct bmc_device *bmc = intf->bmc;

	if ((msg->addr.addr_type != IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
	    || (msg->msg.netfn != IPMI_NETFN_APP_RESPONSE)
	    || (msg->msg.cmd != IPMI_GET_DEVICE_GUID_CMD))
		/* Not for me */
		return;

	if (msg->msg.data[0] != 0) {
		/* Error from getting the GUID, the BMC doesn't have one. */
		bmc->dyn_guid_set = 0;
		goto out;
	}

	if (msg->msg.data_len < 17) {
		bmc->dyn_guid_set = 0;
		dev_warn(intf->si_dev,
			 "The GUID response from the BMC was too short, it was %d but should have been 17.  Assuming GUID is not available.\n",
			 msg->msg.data_len);
		goto out;
	}

	memcpy(bmc->fetch_guid.b, msg->msg.data + 1, 16);
	/*
	 * Make sure the guid data is available before setting
	 * dyn_guid_set.
	 */
	smp_wmb();
	bmc->dyn_guid_set = 1;
 out:
	wake_up(&intf->waitq);
}
