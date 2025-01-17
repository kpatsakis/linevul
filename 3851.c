sctp_disposition_t sctp_sf_do_8_5_1_E_sa(struct net *net,
				      const struct sctp_endpoint *ep,
				      const struct sctp_association *asoc,
				      const sctp_subtype_t type,
				      void *arg,
				      sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk = arg;

	/* Make sure that the SHUTDOWN_ACK chunk has a valid length. */
	if (!sctp_chunk_length_valid(chunk, sizeof(sctp_chunkhdr_t)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Although we do have an association in this case, it corresponds
	 * to a restarted association. So the packet is treated as an OOTB
	 * packet and the state function that handles OOTB SHUTDOWN_ACK is
	 * called with a NULL association.
	 */
	SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);

	return sctp_sf_shut_8_4_5(net, ep, NULL, type, arg, commands);
}
