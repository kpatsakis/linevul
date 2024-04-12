IW_IMPL(unsigned int) iw_get_ui32_e(const iw_byte *b, int endian)
{
	if(endian==IW_ENDIAN_LITTLE)
		return iw_get_ui32le(b);
	return iw_get_ui32be(b);
}
