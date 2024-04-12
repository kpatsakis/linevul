static void platform_device_release(struct device *dev)
{
	struct platform_object *pa = container_of(dev, struct platform_object,
						  pdev.dev);

	of_device_node_put(&pa->pdev.dev);
	kfree(pa->pdev.dev.platform_data);
	kfree(pa->pdev.mfd_cell);
	kfree(pa->pdev.resource);
	kfree(pa->pdev.driver_override);
	kfree(pa);
}
