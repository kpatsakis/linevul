struct sctp_chunkhdr *sctp_inq_peek(struct sctp_inq *queue)
{
	struct sctp_chunk *chunk;
	sctp_chunkhdr_t *ch = NULL;

	chunk = queue->in_progress;
	/* If there is no more chunks in this packet, say so */
	if (chunk->singleton ||
	    chunk->end_of_packet ||
	    chunk->pdiscard)
		    return NULL;

	ch = (sctp_chunkhdr_t *)chunk->chunk_end;

	return ch;
}
