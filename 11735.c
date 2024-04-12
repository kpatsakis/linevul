static inline void read_dev_bar(struct pci_dev *dev,
				struct pci_bar_info *bar_info, int offset,
				u32 len_mask)
{
	int	pos;
	struct resource	*res = dev->resource;

	if (offset == PCI_ROM_ADDRESS || offset == PCI_ROM_ADDRESS1)
		pos = PCI_ROM_RESOURCE;
	else {
		pos = (offset - PCI_BASE_ADDRESS_0) / 4;
		if (pos && ((res[pos - 1].flags & (PCI_BASE_ADDRESS_SPACE |
				PCI_BASE_ADDRESS_MEM_TYPE_MASK)) ==
			   (PCI_BASE_ADDRESS_SPACE_MEMORY |
				PCI_BASE_ADDRESS_MEM_TYPE_64))) {
			bar_info->val = res[pos - 1].start >> 32;
			bar_info->len_val = res[pos - 1].end >> 32;
			return;
		}
	}

	bar_info->val = res[pos].start |
			(res[pos].flags & PCI_REGION_FLAG_MASK);
	bar_info->len_val = resource_size(&res[pos]);
}
