void CL_WriteDemoMessage ( msg_t *msg, int headerBytes ) {
	int		len, swlen;

	len = clc.serverMessageSequence;
	swlen = LittleLong( len );
	FS_Write (&swlen, 4, clc.demofile);
	len = msg->cursize - headerBytes;
	swlen = LittleLong(len);
	FS_Write (&swlen, 4, clc.demofile);
	FS_Write ( msg->data + headerBytes, len, clc.demofile );
}
