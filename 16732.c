efx_tsoh_heap_free(struct efx_tx_queue *tx_queue, struct efx_tso_header *tsoh)
{
	pci_unmap_single(tx_queue->efx->pci_dev,
			 tsoh->dma_addr, tsoh->unmap_len,
			 PCI_DMA_TODEVICE);
	kfree(tsoh);
}
