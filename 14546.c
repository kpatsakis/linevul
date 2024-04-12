char* GetSignatureName(const char* path)
{
	static char szSubjectName[128];
	char *p = NULL, *mpath = NULL;
	BOOL r;
	HMODULE hm;
	HCERTSTORE hStore = NULL;
	HCRYPTMSG hMsg = NULL;
	PCCERT_CONTEXT pCertContext = NULL;
	DWORD dwSize, dwEncoding, dwContentType, dwFormatType, dwSubjectSize;
	PCMSG_SIGNER_INFO pSignerInfo = NULL;
	PCMSG_SIGNER_INFO pCounterSignerInfo = NULL;
	DWORD dwSignerInfo = 0;
	CERT_INFO CertInfo = { 0 };
	SPROG_PUBLISHERINFO ProgPubInfo = { 0 };
	wchar_t *szFileName;

	if (path == NULL) {
		szFileName = calloc(MAX_PATH, sizeof(wchar_t));
		if (szFileName == NULL)
			return NULL;
		hm = GetModuleHandle(NULL);
		if (hm == NULL) {
			uprintf("PKI: Could not get current executable handle: %s", WinPKIErrorString());
			return NULL;
		}
		dwSize = GetModuleFileNameW(hm, szFileName, MAX_PATH);
		if ((dwSize == 0) || ((dwSize == MAX_PATH) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))) {
			uprintf("PKI: Could not get module filename: %s", WinPKIErrorString());
			return NULL;
		}
		mpath = wchar_to_utf8(szFileName);
	} else {
		szFileName = utf8_to_wchar(path);
	}

	r = CryptQueryObject(CERT_QUERY_OBJECT_FILE, szFileName,
		CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED, CERT_QUERY_FORMAT_FLAG_BINARY,
		0, &dwEncoding, &dwContentType, &dwFormatType, &hStore, &hMsg, NULL);
	if (!r) {
		uprintf("PKI: Failed to get signature for '%s': %s", (path==NULL)?mpath:path, WinPKIErrorString());
		goto out;
	}

	r = CryptMsgGetParam(hMsg, CMSG_SIGNER_INFO_PARAM, 0, NULL, &dwSignerInfo);
	if (!r) {
		uprintf("PKI: Failed to get signer size: %s", WinPKIErrorString());
		goto out;
	}

	pSignerInfo = (PCMSG_SIGNER_INFO)calloc(dwSignerInfo, 1);
	if (!pSignerInfo) {
		uprintf("PKI: Could not allocate memory for signer information");
		goto out;
	}

	r = CryptMsgGetParam(hMsg, CMSG_SIGNER_INFO_PARAM, 0, (PVOID)pSignerInfo, &dwSignerInfo);
	if (!r) {
		uprintf("PKI: Failed to get signer information: %s", WinPKIErrorString());
		goto out;
	}

	CertInfo.Issuer = pSignerInfo->Issuer;
	CertInfo.SerialNumber = pSignerInfo->SerialNumber;

	pCertContext = CertFindCertificateInStore(hStore, ENCODING, 0, CERT_FIND_SUBJECT_CERT, (PVOID)&CertInfo, NULL);
	if (!pCertContext) {
		uprintf("PKI: Failed to locate signer certificate in temporary store: %s", WinPKIErrorString());
		goto out;
	}

	dwSubjectSize = CertGetNameStringA(pCertContext, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL,
		szSubjectName, sizeof(szSubjectName));
	if (dwSubjectSize <= 1) {
		uprintf("PKI: Failed to get Subject Name");
		goto out;
	}

	uprintf("Downloaded executable is signed by '%s'", szSubjectName);
	p = szSubjectName;

out:
	safe_free(mpath);
	safe_free(szFileName);
	safe_free(ProgPubInfo.lpszProgramName);
	safe_free(ProgPubInfo.lpszPublisherLink);
	safe_free(ProgPubInfo.lpszMoreInfoLink);
	safe_free(pSignerInfo);
	safe_free(pCounterSignerInfo);
	if (pCertContext != NULL)
		CertFreeCertificateContext(pCertContext);
	if (hStore != NULL)
		CertCloseStore(hStore, 0);
	if (hMsg != NULL)
		CryptMsgClose(hMsg);
	return p;
}
