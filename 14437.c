static int pkcs1_get_salt_len(const TEE_Attribute *params, uint32_t num_params,
			      size_t default_len)
{
	size_t n;

	assert(default_len < INT_MAX);

	for (n = 0; n < num_params; n++) {
		if (params[n].attributeID == TEE_ATTR_RSA_PSS_SALT_LENGTH) {
			if (params[n].content.value.a < INT_MAX)
				return params[n].content.value.a;
			break;
		}
	}
	/*
	 * If salt length isn't provided use the default value which is
	 * the length of the digest.
	 */
	return default_len;
}
