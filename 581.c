static void fwnet_fifo_stop(struct fwnet_device *dev)
{
	if (dev->local_fifo == FWNET_NO_FIFO_ADDR)
		return;

	fw_core_remove_address_handler(&dev->handler);
	dev->local_fifo = FWNET_NO_FIFO_ADDR;
}
