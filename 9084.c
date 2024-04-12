	bool testAddBaseHelper(const wchar_t * base, const wchar_t * rel, const wchar_t * expectedResult, bool backward_compatibility = false) {
		UriParserStateW stateW;

		UriUriW baseUri;
		stateW.uri = &baseUri;
		int res = uriParseUriW(&stateW, base);
		if (res != 0) {
			uriFreeUriMembersW(&baseUri);
			return false;
		}

		UriUriW relUri;
		stateW.uri = &relUri;
		res = uriParseUriW(&stateW, rel);
		if (res != 0) {
			uriFreeUriMembersW(&baseUri);
			uriFreeUriMembersW(&relUri);
			return false;
		}

		UriUriW expectedUri;
		stateW.uri = &expectedUri;
		res = uriParseUriW(&stateW, expectedResult);
		if (res != 0) {
			uriFreeUriMembersW(&baseUri);
			uriFreeUriMembersW(&relUri);
			uriFreeUriMembersW(&expectedUri);
			return false;
		}

		UriUriW transformedUri;
		if (backward_compatibility) {
			res = uriAddBaseUriExW(&transformedUri, &relUri, &baseUri, URI_RESOLVE_IDENTICAL_SCHEME_COMPAT);
		} else {
			res = uriAddBaseUriW(&transformedUri, &relUri, &baseUri);
		}

		if (res != 0) {
			uriFreeUriMembersW(&baseUri);
			uriFreeUriMembersW(&relUri);
			uriFreeUriMembersW(&expectedUri);
			uriFreeUriMembersW(&transformedUri);
			return false;
		}

		const bool equal = (URI_TRUE == uriEqualsUriW(&transformedUri, &expectedUri));
		if (!equal) {
			wchar_t transformedUriText[1024 * 8];
			wchar_t expectedUriText[1024 * 8];
			uriToStringW(transformedUriText, &transformedUri, 1024 * 8, NULL);
			uriToStringW(expectedUriText, &expectedUri, 1024 * 8, NULL);
#ifdef HAVE_WPRINTF
			wprintf(L"\n\n\nExpected: \"%s\"\nReceived: \"%s\"\n\n\n", expectedUriText, transformedUriText);
#endif
		}

		uriFreeUriMembersW(&baseUri);
		uriFreeUriMembersW(&relUri);
		uriFreeUriMembersW(&expectedUri);
		uriFreeUriMembersW(&transformedUri);
		return equal;
	}
