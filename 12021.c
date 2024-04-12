static void __dma_free_coherent(struct device *dev, size_t size,
				void *vaddr, dma_addr_t dma_handle,
				struct dma_attrs *attrs)
{
	bool freed;
	phys_addr_t paddr = dma_to_phys(dev, dma_handle);

	if (dev == NULL) {
		WARN_ONCE(1, "Use an actual device structure for DMA allocation\n");
		return;
	}

	freed = dma_release_from_contiguous(dev,
					phys_to_page(paddr),
					size >> PAGE_SHIFT);
	if (!freed)
		swiotlb_free_coherent(dev, size, vaddr, dma_handle);
}
