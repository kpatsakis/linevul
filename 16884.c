static void rle_write_trns(struct rle_context *rlectx, int num_trns)
{
	iw_byte dstbuf[4];
	int num_remaining = num_trns;
	int num_to_write;

	while(num_remaining>0) {
		num_to_write = num_remaining;
		if(num_to_write>255) num_to_write=255;
		dstbuf[0]=0x00; // 00 02 = Delta
		dstbuf[1]=0x02;
		dstbuf[2]=(iw_byte)num_to_write; // X offset
		dstbuf[3]=0x00; // Y offset
		iwbmp_write(rlectx->wctx,dstbuf,4);
		rlectx->total_bytes_written+=4;
		num_remaining -= num_to_write;
	}
	rlectx->pending_data_start += num_trns;
}
