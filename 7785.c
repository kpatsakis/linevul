int dm_persistent_snapshot_init(void)
{
	int r;

	r = dm_exception_store_type_register(&_persistent_type);
	if (r) {
		DMERR("Unable to register persistent exception store type");
		return r;
	}

	r = dm_exception_store_type_register(&_persistent_compat_type);
	if (r) {
		DMERR("Unable to register old-style persistent exception "
		      "store type");
		dm_exception_store_type_unregister(&_persistent_type);
		return r;
	}

	return r;
}
