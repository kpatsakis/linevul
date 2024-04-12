static void arm_dma_sync_single_for_device(struct device *dev,
		dma_addr_t handle, size_t size, enum dma_data_direction dir)
{
	unsigned int offset = handle & (PAGE_SIZE - 1);
	struct page *page = pfn_to_page(dma_to_pfn(dev, handle-offset));
	__dma_page_cpu_to_dev(page, offset, size, dir);
}
