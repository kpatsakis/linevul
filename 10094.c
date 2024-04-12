void sctp_chunk_assign_ssn(struct sctp_chunk *chunk)
{
	struct sctp_datamsg *msg;
	struct sctp_chunk *lchunk;
	struct sctp_stream *stream;
	__u16 ssn;
	__u16 sid;

	if (chunk->has_ssn)
		return;

	/* All fragments will be on the same stream */
	sid = ntohs(chunk->subh.data_hdr->stream);
	stream = &chunk->asoc->ssnmap->out;

	/* Now assign the sequence number to the entire message.
	 * All fragments must have the same stream sequence number.
	 */
	msg = chunk->msg;
	list_for_each_entry(lchunk, &msg->chunks, frag_list) {
		if (lchunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) {
			ssn = 0;
		} else {
			if (lchunk->chunk_hdr->flags & SCTP_DATA_LAST_FRAG)
				ssn = sctp_ssn_next(stream, sid);
			else
				ssn = sctp_ssn_peek(stream, sid);
		}

		lchunk->subh.data_hdr->ssn = htons(ssn);
		lchunk->has_ssn = 1;
	}
}