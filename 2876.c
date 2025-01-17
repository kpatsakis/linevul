rx_print(netdissect_options *ndo,
         register const u_char *bp, int length, int sport, int dport,
         const u_char *bp2)
{
	register const struct rx_header *rxh;
	int i;
	int32_t opcode;

	if (ndo->ndo_snapend - bp < (int)sizeof (struct rx_header)) {
		ND_PRINT((ndo, " [|rx] (%d)", length));
		return;
	}

	rxh = (const struct rx_header *) bp;

	ND_PRINT((ndo, " rx %s", tok2str(rx_types, "type %d", rxh->type)));

	if (ndo->ndo_vflag) {
		int firstflag = 0;

		if (ndo->ndo_vflag > 1)
			ND_PRINT((ndo, " cid %08x call# %d",
			       (int) EXTRACT_32BITS(&rxh->cid),
			       (int) EXTRACT_32BITS(&rxh->callNumber)));

		ND_PRINT((ndo, " seq %d ser %d",
		       (int) EXTRACT_32BITS(&rxh->seq),
		       (int) EXTRACT_32BITS(&rxh->serial)));

		if (ndo->ndo_vflag > 2)
			ND_PRINT((ndo, " secindex %d serviceid %hu",
				(int) rxh->securityIndex,
				EXTRACT_16BITS(&rxh->serviceId)));

		if (ndo->ndo_vflag > 1)
			for (i = 0; i < NUM_RX_FLAGS; i++) {
				if (rxh->flags & rx_flags[i].flag &&
				    (!rx_flags[i].packetType ||
				     rxh->type == rx_flags[i].packetType)) {
					if (!firstflag) {
						firstflag = 1;
						ND_PRINT((ndo, " "));
					} else {
						ND_PRINT((ndo, ","));
					}
					ND_PRINT((ndo, "<%s>", rx_flags[i].s));
				}
			}
	}

	/*
	 * Try to handle AFS calls that we know about.  Check the destination
	 * port and make sure it's a data packet.  Also, make sure the
	 * seq number is 1 (because otherwise it's a continuation packet,
	 * and we can't interpret that).  Also, seems that reply packets
	 * do not have the client-init flag set, so we check for that
	 * as well.
	 */

	if (rxh->type == RX_PACKET_TYPE_DATA &&
	    EXTRACT_32BITS(&rxh->seq) == 1 &&
	    rxh->flags & RX_CLIENT_INITIATED) {

		/*
		 * Insert this call into the call cache table, so we
		 * have a chance to print out replies
		 */

		rx_cache_insert(ndo, bp, (const struct ip *) bp2, dport);

		switch (dport) {
			case FS_RX_PORT:	/* AFS file service */
				fs_print(ndo, bp, length);
				break;
			case CB_RX_PORT:	/* AFS callback service */
				cb_print(ndo, bp, length);
				break;
			case PROT_RX_PORT:	/* AFS protection service */
				prot_print(ndo, bp, length);
				break;
			case VLDB_RX_PORT:	/* AFS VLDB service */
				vldb_print(ndo, bp, length);
				break;
			case KAUTH_RX_PORT:	/* AFS Kerberos auth service */
				kauth_print(ndo, bp, length);
				break;
			case VOL_RX_PORT:	/* AFS Volume service */
				vol_print(ndo, bp, length);
				break;
			case BOS_RX_PORT:	/* AFS BOS service */
				bos_print(ndo, bp, length);
				break;
			default:
				;
		}

	/*
	 * If it's a reply (client-init is _not_ set, but seq is one)
	 * then look it up in the cache.  If we find it, call the reply
	 * printing functions  Note that we handle abort packets here,
	 * because printing out the return code can be useful at times.
	 */

	} else if (((rxh->type == RX_PACKET_TYPE_DATA &&
					EXTRACT_32BITS(&rxh->seq) == 1) ||
		    rxh->type == RX_PACKET_TYPE_ABORT) &&
		   (rxh->flags & RX_CLIENT_INITIATED) == 0 &&
		   rx_cache_find(rxh, (const struct ip *) bp2,
				 sport, &opcode)) {

		switch (sport) {
			case FS_RX_PORT:	/* AFS file service */
				fs_reply_print(ndo, bp, length, opcode);
				break;
			case CB_RX_PORT:	/* AFS callback service */
				cb_reply_print(ndo, bp, length, opcode);
				break;
			case PROT_RX_PORT:	/* AFS PT service */
				prot_reply_print(ndo, bp, length, opcode);
				break;
			case VLDB_RX_PORT:	/* AFS VLDB service */
				vldb_reply_print(ndo, bp, length, opcode);
				break;
			case KAUTH_RX_PORT:	/* AFS Kerberos auth service */
				kauth_reply_print(ndo, bp, length, opcode);
				break;
			case VOL_RX_PORT:	/* AFS Volume service */
				vol_reply_print(ndo, bp, length, opcode);
				break;
			case BOS_RX_PORT:	/* AFS BOS service */
				bos_reply_print(ndo, bp, length, opcode);
				break;
			default:
				;
		}

	/*
	 * If it's an RX ack packet, then use the appropriate ack decoding
	 * function (there isn't any service-specific information in the
	 * ack packet, so we can use one for all AFS services)
	 */

	} else if (rxh->type == RX_PACKET_TYPE_ACK)
		rx_ack_print(ndo, bp, length);


	ND_PRINT((ndo, " (%d)", length));
}
