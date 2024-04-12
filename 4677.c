write_publickey (struct sc_card *card, unsigned int offset,
				const unsigned char *buf, size_t count)
{
	struct auth_update_component_info args;
	struct sc_pkcs15_pubkey_rsa key;
	int ii, rv;
	size_t len = 0, der_size = 0;

	LOG_FUNC_CALLED(card->ctx);

	sc_log_hex(card->ctx, "write_publickey", buf, count);

	if (1+offset > sizeof(rsa_der))
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Invalid offset value");

	len = offset+count > sizeof(rsa_der) ? sizeof(rsa_der) - offset : count;

	memcpy(rsa_der + offset, buf, len);
	rsa_der_len = offset + len;

	if (rsa_der[0]==0x30)   {
		if (rsa_der[1] & 0x80)
			for (ii=0; ii < (rsa_der[1]&0x0F); ii++)
				der_size = der_size*0x100 + rsa_der[2+ii];
		else
			der_size = rsa_der[1];
	}

	sc_log(card->ctx, "der_size %"SC_FORMAT_LEN_SIZE_T"u", der_size);
	if (offset + len < der_size + 2)
		LOG_FUNC_RETURN(card->ctx, len);

	rv = sc_pkcs15_decode_pubkey_rsa(card->ctx, &key, rsa_der, rsa_der_len);
	rsa_der_len = 0;
	memset(rsa_der, 0, sizeof(rsa_der));
	LOG_TEST_RET(card->ctx, rv, "cannot decode public key");

	memset(&args, 0, sizeof(args));
	args.type = SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC;
	args.component = 1;
	args.data = key.modulus.data;
	args.len = key.modulus.len;
	rv = auth_update_component(card, &args);
	LOG_TEST_RET(card->ctx, rv, "Update component failed");

	memset(&args, 0, sizeof(args));
	args.type = SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC;
	args.component = 2;
	args.data = key.exponent.data;
	args.len = key.exponent.len;
	rv = auth_update_component(card, &args);
	LOG_TEST_RET(card->ctx, rv, "Update component failed");

	LOG_FUNC_RETURN(card->ctx, len);
}
