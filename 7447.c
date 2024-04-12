void MSG_WriteLong( msg_t *sb, int c ) {
	MSG_WriteBits( sb, c, 32 );
}
