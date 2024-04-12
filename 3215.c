static void my_skip_input_data_fn(j_decompress_ptr cinfo, long num_bytes)
{
	struct iwjpegrcontext *rctx = (struct iwjpegrcontext*)cinfo->src;
	size_t bytes_still_to_skip;
	size_t nbytes;
	int ret;
	size_t bytesread;

	if(num_bytes<=0) return;
	bytes_still_to_skip = (size_t)num_bytes;

	while(bytes_still_to_skip>0) {
		if(rctx->pub.bytes_in_buffer>0) {
			nbytes = rctx->pub.bytes_in_buffer;
			if(nbytes>bytes_still_to_skip)
				nbytes = bytes_still_to_skip;

			rctx->pub.bytes_in_buffer -= nbytes;
			rctx->pub.next_input_byte += nbytes;
			bytes_still_to_skip -= nbytes;
		}

		if(bytes_still_to_skip<1) return;

		ret = (*rctx->iodescr->read_fn)(rctx->ctx,rctx->iodescr,
			rctx->buffer,rctx->buffer_len,&bytesread);
		if(!ret) bytesread=0;

		rctx->pub.next_input_byte = rctx->buffer;
		rctx->pub.bytes_in_buffer = bytesread;
	}
}
