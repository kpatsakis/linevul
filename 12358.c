static void process_level0_os9_area(LHAFileHeader *header,
                                    uint8_t *data, size_t data_len)
{


	if (data_len < LEVEL_0_OS9_EXTENDED_LEN
	 || data[9] != 0xcc || data[1] != data[17] || data[2] != data[18]) {
		return;
	}


	header->os_type = LHA_OS_TYPE_OS9;
	header->os9_perms = lha_decode_uint16(data + 1);
	header->extra_flags |= LHA_FILE_OS9_PERMS;
}
