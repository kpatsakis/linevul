static void __devexit airo_pci_remove(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);

	airo_print_info(dev->name, "Unregistering...");
	stop_airo_card(dev, 1);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}
