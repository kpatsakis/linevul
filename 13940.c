static struct wdm_device *wdm_find_device_by_minor(int minor)
{
	struct wdm_device *desc;

	spin_lock(&wdm_device_list_lock);
	list_for_each_entry(desc, &wdm_device_list, device_list)
		if (desc->intf->minor == minor)
			goto found;
	desc = NULL;
found:
	spin_unlock(&wdm_device_list_lock);

	return desc;
}
