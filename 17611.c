static int asepcos_build_pin_apdu(sc_card_t *card, sc_apdu_t *apdu,
	struct sc_pin_cmd_data *data, u8 *buf, size_t buf_len,
	unsigned int cmd, int is_puk)
{
	int r, fileid;
	u8  *p = buf;
	sc_cardctl_asepcos_akn2fileid_t st;

	switch (cmd) {
	case SC_PIN_CMD_VERIFY:
		st.akn = data->pin_reference;
		r = asepcos_akn_to_fileid(card, &st);
		if (r != SC_SUCCESS)
			return r;
		fileid = st.fileid;
		/* the fileid of the puk is the fileid of the pin + 1 */
		if (is_puk != 0)
			fileid++;
		sc_format_apdu(card, apdu, SC_APDU_CASE_3_SHORT, 0x20, 0x02, 0x80);
		*p++ = (fileid >> 24) & 0xff;
		*p++ = (fileid >> 16) & 0xff;
		*p++ = (fileid >> 8 ) & 0xff;
		*p++ = fileid & 0xff;
		memcpy(p, data->pin1.data, data->pin1.len);
		p += data->pin1.len;
		apdu->lc       = p - buf;
		apdu->datalen  = p - buf;
		apdu->data     = buf;
		break;
	case SC_PIN_CMD_CHANGE:
		/* build the CHANGE KEY apdu. Note: the PIN file is implicitly
		 * selected by its SFID */
		*p++ = 0x81;
		*p++ = data->pin2.len & 0xff;
		memcpy(p, data->pin2.data, data->pin2.len);
		p   += data->pin2.len;
		st.akn = data->pin_reference;
		r = asepcos_akn_to_fileid(card, &st);
		if (r != SC_SUCCESS)
			return r;
		fileid = 0x80 | (st.fileid & 0x1f);
		sc_format_apdu(card, apdu, SC_APDU_CASE_3_SHORT, 0x24, 0x01, fileid);
		apdu->lc       = p - buf;
		apdu->datalen  = p - buf;
		apdu->data     = buf;
		break;
	case SC_PIN_CMD_UNBLOCK:
		/* build the UNBLOCK KEY apdu. The PIN file is implicitly 
		 * selected by its SFID. The new PIN is provided in the
		 * data field of the UNBLOCK KEY command. */
		*p++ = 0x81;
		*p++ = data->pin2.len & 0xff;
		memcpy(p, data->pin2.data, data->pin2.len);
		p   += data->pin2.len;
		st.akn = data->pin_reference;
		r = asepcos_akn_to_fileid(card, &st);
		if (r != SC_SUCCESS)
			return r;
		fileid = 0x80 | (st.fileid & 0x1f);
		sc_format_apdu(card, apdu, SC_APDU_CASE_3_SHORT, 0x2C, 0x02, fileid);
		apdu->lc       = p - buf;
		apdu->datalen  = p - buf;
		apdu->data     = buf;
		break;
	default:
		return SC_ERROR_NOT_SUPPORTED;
	}
	return SC_SUCCESS;
}
