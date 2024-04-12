void rdp_write_security_header(STREAM* s, UINT16 flags)
{
	/* Basic Security Header */
	stream_write_UINT16(s, flags); /* flags */
	stream_write_UINT16(s, 0); /* flagsHi (unused) */
}
