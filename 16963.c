BOOL nla_verify_header(wStream* s)
{
	if ((s->pointer[0] == 0x30) && (s->pointer[1] & 0x80))
		return TRUE;

	return FALSE;
}
