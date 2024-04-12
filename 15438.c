static TEE_Result tee_svc_obj_generate_key_rsa(
	struct tee_obj *o, const struct tee_cryp_obj_type_props *type_props,
	uint32_t key_size,
	const TEE_Attribute *params, uint32_t param_count)
{
	TEE_Result res;
	struct rsa_keypair *key = o->attr;
	uint32_t e = TEE_U32_TO_BIG_ENDIAN(65537);

	/* Copy the present attributes into the obj before starting */
	res = tee_svc_cryp_obj_populate_type(o, type_props, params,
					     param_count);
	if (res != TEE_SUCCESS)
		return res;
	if (!get_attribute(o, type_props, TEE_ATTR_RSA_PUBLIC_EXPONENT))
		crypto_bignum_bin2bn((const uint8_t *)&e, sizeof(e), key->e);
	res = crypto_acipher_gen_rsa_key(key, key_size);
	if (res != TEE_SUCCESS)
		return res;

	/* Set bits for all known attributes for this object type */
	o->have_attrs = (1 << type_props->num_type_attrs) - 1;

	return TEE_SUCCESS;
}
