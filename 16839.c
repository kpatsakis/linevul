void FAST_FUNC udhcp_add_simple_option(struct dhcp_packet *packet, uint8_t code, uint32_t data)
{
	const struct dhcp_optflag *dh;

	for (dh = dhcp_optflags; dh->code; dh++) {
		if (dh->code == code) {
			uint8_t option[6], len;

			option[OPT_CODE] = code;
			len = dhcp_option_lengths[dh->flags & OPTION_TYPE_MASK];
			option[OPT_LEN] = len;
			if (BB_BIG_ENDIAN)
				data <<= 8 * (4 - len);
			/* Assignment is unaligned! */
			move_to_unaligned32(&option[OPT_DATA], data);
			udhcp_add_binary_option(packet, option);
			return;
		}
	}

	bb_error_msg("can't add option 0x%02x", code);
}
