static void sctp_cmd_assoc_change(sctp_cmd_seq_t *commands,
				 struct sctp_association *asoc,
				 u8 state)
{
	struct sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_assoc_change(asoc, 0, state, 0,
					    asoc->c.sinit_num_ostreams,
					    asoc->c.sinit_max_instreams,
					    NULL, GFP_ATOMIC);
	if (ev)
		sctp_ulpq_tail_event(&asoc->ulpq, ev);
}
