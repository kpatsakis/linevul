static void * cm_copy_private_data(const void *private_data,
				   u8 private_data_len)
{
	void *data;

	if (!private_data || !private_data_len)
		return NULL;

	data = kmemdup(private_data, private_data_len, GFP_KERNEL);
	if (!data)
		return ERR_PTR(-ENOMEM);

	return data;
}
