static void arm_iommu_unmap_page(struct device *dev, dma_addr_t handle,
		size_t size, enum dma_data_direction dir,
		struct dma_attrs *attrs)
{
	struct dma_iommu_mapping *mapping = dev->archdata.mapping;
	dma_addr_t iova = handle & PAGE_MASK;
	struct page *page = phys_to_page(iommu_iova_to_phys(mapping->domain, iova));
	int offset = handle & ~PAGE_MASK;
	int len = PAGE_ALIGN(size + offset);

	if (!iova)
		return;

	if (!dma_get_attr(DMA_ATTR_SKIP_CPU_SYNC, attrs))
		__dma_page_dev_to_cpu(page, offset, size, dir);

	iommu_unmap(mapping->domain, iova, len);
	__free_iova(mapping, iova, len);
}
