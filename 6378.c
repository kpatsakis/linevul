void MSG_WriteShort( msg_t *sb, int c ) {
#ifdef PARANOID
	if (c < ((short)0x8000) || c > (short)0x7fff)
		Com_Error (ERR_FATAL, "MSG_WriteShort: range error");
#endif

	MSG_WriteBits( sb, c, 16 );
}
