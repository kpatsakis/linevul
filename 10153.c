static int bist_write(struct pci_dev *dev, int offset, u8 value, void *data)
{
	u8 cur_value;
	int err;

	err = pci_read_config_byte(dev, offset, &cur_value);
	if (err)
		goto out;

	if ((cur_value & ~PCI_BIST_START) == (value & ~PCI_BIST_START)
	    || value == PCI_BIST_START)
		err = pci_write_config_byte(dev, offset, value);

out:
	return err;
}
