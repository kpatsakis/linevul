auth_process_fci(struct sc_card *card, struct sc_file *file,
            const unsigned char *buf, size_t buflen)
{
	unsigned char type, attr[SC_OBERTHUR_MAX_ATTR_SIZE];
	int attr_len = sizeof(attr);

	LOG_FUNC_CALLED(card->ctx);
	attr_len = sizeof(attr);
	if (tlv_get(buf, buflen, 0x82, attr, &attr_len))
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
	type = attr[0];

	attr_len = sizeof(attr);
	if (tlv_get(buf, buflen, 0x83, attr, &attr_len))
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
	file->id = attr[0]*0x100 + attr[1];

	attr_len = sizeof(attr);
	if (tlv_get(buf, buflen, type==0x01 ? 0x80 : 0x85, attr, &attr_len))
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
	if (attr_len<2 && type != 0x04)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);

	switch (type) {
	case 0x01:
		file->type = SC_FILE_TYPE_WORKING_EF;
		file->ef_structure = SC_FILE_EF_TRANSPARENT;
		file->size = attr[0]*0x100 + attr[1];
		break;
	case 0x04:
		file->type = SC_FILE_TYPE_WORKING_EF;
		file->ef_structure = SC_FILE_EF_LINEAR_VARIABLE;
		file->size = attr[0];
		attr_len = sizeof(attr);
		if (tlv_get(buf, buflen, 0x82, attr, &attr_len))
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
		if (attr_len!=5)
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
		file->record_length = attr[2]*0x100+attr[3];
		file->record_count = attr[4];
		break;
	case 0x11:
		file->type = SC_FILE_TYPE_INTERNAL_EF;
		file->ef_structure = SC_CARDCTL_OBERTHUR_KEY_DES;
		file->size = attr[0]*0x100 + attr[1];
		file->size /= 8;
		break;
	case 0x12:
		file->type = SC_FILE_TYPE_INTERNAL_EF;
		file->ef_structure = SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC;

		file->size = attr[0]*0x100 + attr[1];
		if (file->size==512)
			file->size = PUBKEY_512_ASN1_SIZE;
		else if (file->size==1024)
			file->size = PUBKEY_1024_ASN1_SIZE;
		else if (file->size==2048)
			file->size = PUBKEY_2048_ASN1_SIZE;
		else   {
			sc_log(card->ctx,
			       "Not supported public key size: %"SC_FORMAT_LEN_SIZE_T"u",
			       file->size);
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
		}
		break;
	case 0x14:
		file->type = SC_FILE_TYPE_INTERNAL_EF;
		file->ef_structure = SC_CARDCTL_OBERTHUR_KEY_RSA_CRT;
		file->size = attr[0]*0x100 + attr[1];
		break;
	case 0x38:
		file->type = SC_FILE_TYPE_DF;
		file->size = attr[0];
		if (SC_SUCCESS != sc_file_set_type_attr(file,attr,attr_len))
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
		break;
	default:
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
	}

	attr_len = sizeof(attr);
	if (tlv_get(buf, buflen, 0x86, attr, &attr_len))
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);
	if (attr_len<8)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_UNKNOWN_DATA_RECEIVED);

	if (file->type == SC_FILE_TYPE_DF) {
		add_acl_entry(card, file, SC_AC_OP_CREATE, attr[0]);
		add_acl_entry(card, file, SC_AC_OP_CRYPTO, attr[1]);
		add_acl_entry(card, file, SC_AC_OP_LIST_FILES, attr[2]);
		add_acl_entry(card, file, SC_AC_OP_DELETE, attr[3]);
		add_acl_entry(card, file, SC_AC_OP_PIN_DEFINE, attr[4]);
		add_acl_entry(card, file, SC_AC_OP_PIN_CHANGE, attr[5]);
		add_acl_entry(card, file, SC_AC_OP_PIN_RESET, attr[6]);
		sc_log(card->ctx, "SC_FILE_TYPE_DF:CRYPTO %X", attr[1]);
	}
	else if (file->type == SC_FILE_TYPE_INTERNAL_EF)  { /* EF */
		switch (file->ef_structure) {
		case SC_CARDCTL_OBERTHUR_KEY_DES:
			add_acl_entry(card, file, SC_AC_OP_UPDATE, attr[0]);
			add_acl_entry(card, file, SC_AC_OP_PSO_DECRYPT, attr[1]);
			add_acl_entry(card, file, SC_AC_OP_PSO_ENCRYPT, attr[2]);
			add_acl_entry(card, file, SC_AC_OP_PSO_COMPUTE_CHECKSUM, attr[3]);
			add_acl_entry(card, file, SC_AC_OP_PSO_VERIFY_CHECKSUM, attr[4]);
			add_acl_entry(card, file, SC_AC_OP_INTERNAL_AUTHENTICATE, attr[5]);
			add_acl_entry(card, file, SC_AC_OP_EXTERNAL_AUTHENTICATE, attr[6]);
			break;
		case SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC:
			add_acl_entry(card, file, SC_AC_OP_UPDATE, attr[0]);
			add_acl_entry(card, file, SC_AC_OP_PSO_ENCRYPT, attr[2]);
			add_acl_entry(card, file, SC_AC_OP_PSO_VERIFY_SIGNATURE, attr[4]);
			add_acl_entry(card, file, SC_AC_OP_EXTERNAL_AUTHENTICATE, attr[6]);
			break;
		case SC_CARDCTL_OBERTHUR_KEY_RSA_CRT:
			add_acl_entry(card, file, SC_AC_OP_UPDATE, attr[0]);
			add_acl_entry(card, file, SC_AC_OP_PSO_DECRYPT, attr[1]);
			add_acl_entry(card, file, SC_AC_OP_PSO_COMPUTE_SIGNATURE, attr[3]);
			add_acl_entry(card, file, SC_AC_OP_INTERNAL_AUTHENTICATE, attr[5]);
			break;
		}
	}
	else   {
		switch (file->ef_structure) {
		case SC_FILE_EF_TRANSPARENT:
			add_acl_entry(card, file, SC_AC_OP_WRITE, attr[0]);
			add_acl_entry(card, file, SC_AC_OP_UPDATE, attr[1]);
			add_acl_entry(card, file, SC_AC_OP_READ, attr[2]);
			add_acl_entry(card, file, SC_AC_OP_ERASE, attr[3]);
			break;
		case SC_FILE_EF_LINEAR_VARIABLE:
			add_acl_entry(card, file, SC_AC_OP_WRITE, attr[0]);
			add_acl_entry(card, file, SC_AC_OP_UPDATE, attr[1]);
			add_acl_entry(card, file, SC_AC_OP_READ, attr[2]);
			add_acl_entry(card, file, SC_AC_OP_ERASE, attr[3]);
			break;
		}
	}

	file->status = SC_FILE_STATUS_ACTIVATED;
	file->magic = SC_FILE_MAGIC;

	LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
}
