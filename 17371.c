authentic_sm_free_wrapped_apdu(struct sc_card *card, struct sc_apdu *plain, struct sc_apdu **sm_apdu)
{
	struct sc_context *ctx = card->ctx;

	LOG_FUNC_CALLED(ctx);
	if (!sm_apdu)
		LOG_FUNC_RETURN(ctx, SC_ERROR_INVALID_ARGUMENTS);
        if (!(*sm_apdu))
		LOG_FUNC_RETURN(ctx, SC_SUCCESS);

        if (plain)   {
		if (plain->resplen < (*sm_apdu)->resplen)
			LOG_TEST_RET(ctx, SC_ERROR_BUFFER_TOO_SMALL, "Insufficient plain APDU response size");
		memcpy(plain->resp, (*sm_apdu)->resp, (*sm_apdu)->resplen);
		plain->resplen = (*sm_apdu)->resplen;
		plain->sw1 = (*sm_apdu)->sw1;
		plain->sw2 = (*sm_apdu)->sw2;
	}

	if ((*sm_apdu)->data)
		free((unsigned char *) (*sm_apdu)->data);
	if ((*sm_apdu)->resp)
		free((unsigned char *) (*sm_apdu)->resp);

	free(*sm_apdu);
	*sm_apdu = NULL;
	LOG_FUNC_RETURN(ctx, SC_SUCCESS);
}
