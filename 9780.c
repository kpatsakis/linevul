void credssp_buffer_print(rdpCredssp* credssp)
{
	if (credssp->negoToken.cbBuffer > 0)
	{
		fprintf(stderr, "CredSSP.negoToken (length = %d):\n", (int) credssp->negoToken.cbBuffer);
		winpr_HexDump(credssp->negoToken.pvBuffer, credssp->negoToken.cbBuffer);
	}

	if (credssp->pubKeyAuth.cbBuffer > 0)
	{
		fprintf(stderr, "CredSSP.pubKeyAuth (length = %d):\n", (int) credssp->pubKeyAuth.cbBuffer);
		winpr_HexDump(credssp->pubKeyAuth.pvBuffer, credssp->pubKeyAuth.cbBuffer);
	}

	if (credssp->authInfo.cbBuffer > 0)
	{
		fprintf(stderr, "CredSSP.authInfo (length = %d):\n", (int) credssp->authInfo.cbBuffer);
		winpr_HexDump(credssp->authInfo.pvBuffer, credssp->authInfo.cbBuffer);
	}
}
