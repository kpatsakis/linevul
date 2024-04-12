 int trace_list_calls(void *buff, size_t buff_size, size_t *needed)
 {
 	struct trace_output_hdr *output_hdr = NULL;
	void *end, *ptr = buff;
	size_t rec, upto;
	size_t count;

	end = buff ? buff + buff_size : NULL;

	/* Place some header information */
	if (ptr + sizeof(struct trace_output_hdr) < end)
		output_hdr = ptr;
	ptr += sizeof(struct trace_output_hdr);

	/* Add information about each call */
	count = hdr->ftrace_count;
	if (count > hdr->ftrace_size)
		count = hdr->ftrace_size;
	for (rec = upto = 0; rec < count; rec++) {
		if (ptr + sizeof(struct trace_call) < end) {
			struct trace_call *call = &hdr->ftrace[rec];
			struct trace_call *out = ptr;

			out->func = call->func * FUNC_SITE_SIZE;
			out->caller = call->caller * FUNC_SITE_SIZE;
			out->flags = call->flags;
			upto++;
		}
		ptr += sizeof(struct trace_call);
	}

	/* Update the header */
	if (output_hdr) {
		output_hdr->rec_count = upto;
		output_hdr->type = TRACE_CHUNK_CALLS;
	}

	/* Work out how must of the buffer we used */
	*needed = ptr - buff;
	if (ptr > end)
		return -ENOSPC;

 	return 0;
 }
