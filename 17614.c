static int network_packetsize(size_t received, void *payload)
{
	struct network_packetsize_payload *npp = (struct network_packetsize_payload*)payload;

	/* Accumulate bytes */
	npp->stats->received_bytes += received;

	/* Fire notification if the threshold is reached */
	if ((npp->stats->received_bytes - npp->last_fired_bytes) > NETWORK_XFER_THRESHOLD) {
		npp->last_fired_bytes = npp->stats->received_bytes;

		if (npp->callback(npp->stats, npp->payload))
			return GIT_EUSER;
	}

	return 0;
}
