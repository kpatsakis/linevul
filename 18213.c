OJPEGWriteStreamDri(TIFF* tif, void** mem, uint32* len)
{
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	assert(OJPEG_BUFFER>=6);
	if (sp->restart_interval!=0)
	{
		sp->out_buffer[0]=255;
		sp->out_buffer[1]=JPEG_MARKER_DRI;
		sp->out_buffer[2]=0;
		sp->out_buffer[3]=4;
		sp->out_buffer[4]=(sp->restart_interval>>8);
		sp->out_buffer[5]=(sp->restart_interval&255);
		*len=6;
		*mem=(void*)sp->out_buffer;
	}
	sp->out_state++;
}
