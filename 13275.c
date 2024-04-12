BOOL rdp_read_header(rdpRdp* rdp, STREAM* s, UINT16* length, UINT16* channel_id)
{
	UINT16 initiator;
	enum DomainMCSPDU MCSPDU;

	MCSPDU = (rdp->settings->ServerMode) ? DomainMCSPDU_SendDataRequest : DomainMCSPDU_SendDataIndication;

	if (!mcs_read_domain_mcspdu_header(s, &MCSPDU, length))
	{
		if (MCSPDU != DomainMCSPDU_DisconnectProviderUltimatum)
			return FALSE;
	}

	if (*length - 8 > stream_get_left(s))
		return FALSE;

	if (MCSPDU == DomainMCSPDU_DisconnectProviderUltimatum)
	{
		BYTE reason;

		(void) per_read_enumerated(s, &reason, 0);
		DEBUG_RDP("DisconnectProviderUltimatum from server, reason code 0x%02x\n", reason);

		rdp->disconnect = TRUE;

		return TRUE;
	}

	if(stream_get_left(s) < 5)
		return FALSE;
	per_read_integer16(s, &initiator, MCS_BASE_CHANNEL_ID); /* initiator (UserId) */
	per_read_integer16(s, channel_id, 0); /* channelId */
	stream_seek(s, 1); /* dataPriority + Segmentation (0x70) */

	if(!per_read_length(s, length)) /* userData (OCTET_STRING) */
		return FALSE;
	if (*length > stream_get_left(s))
		return FALSE;

	return TRUE;
}
