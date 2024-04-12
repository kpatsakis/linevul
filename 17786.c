static TEE_Result op_attr_bignum_from_user(void *attr, const void *buffer,
					   size_t size)
{
	struct bignum **bn = attr;

	return crypto_bignum_bin2bn(buffer, size, *bn);
}
