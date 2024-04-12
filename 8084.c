static int dcb_app_add(const struct dcb_app *app, int ifindex)
{
	struct dcb_app_type *entry;

	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry)
		return -ENOMEM;

	memcpy(&entry->app, app, sizeof(*app));
	entry->ifindex = ifindex;
	list_add(&entry->list, &dcb_app_list);

	return 0;
}
