static struct pstore *get_info(struct dm_exception_store *store)
{
	return (struct pstore *) store->context;
}
