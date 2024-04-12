static void sctp_cmd_setup_t4(sctp_cmd_seq_t *cmds,
				struct sctp_association *asoc,
				struct sctp_chunk *chunk)
{
	struct sctp_transport *t;

	t = sctp_assoc_choose_alter_transport(asoc, chunk->transport);
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T4_RTO] = t->rto;
	chunk->transport = t;
}
