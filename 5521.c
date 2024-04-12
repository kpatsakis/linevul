SECURITY_STATUS SEC_ENTRY AcceptSecurityContext(PCredHandle phCredential, PCtxtHandle phContext,
		PSecBufferDesc pInput, ULONG fContextReq, ULONG TargetDataRep, PCtxtHandle phNewContext,
		PSecBufferDesc pOutput, PULONG pfContextAttr, PTimeStamp ptsTimeStamp)
{
	char* Name;
	SECURITY_STATUS status;
	SecurityFunctionTableA* table;

	Name = (char*) sspi_SecureHandleGetUpperPointer(phCredential);

	if (!Name)
		return SEC_E_SECPKG_NOT_FOUND;

	table = sspi_GetSecurityFunctionTableAByNameA(Name);

	if (!table)
		return SEC_E_SECPKG_NOT_FOUND;

	if (table->AcceptSecurityContext == NULL)
		return SEC_E_UNSUPPORTED_FUNCTION;

	status = table->AcceptSecurityContext(phCredential, phContext, pInput, fContextReq,
			TargetDataRep, phNewContext, pOutput, pfContextAttr, ptsTimeStamp);

	return status;
}
