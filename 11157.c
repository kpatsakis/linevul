file_mbswidth(const char *s)
{
#if defined(HAVE_WCHAR_H) && defined(HAVE_MBRTOWC) && defined(HAVE_WCWIDTH)
	size_t bytesconsumed, old_n, n, width = 0;
	mbstate_t state;
	wchar_t nextchar;
	(void)memset(&state, 0, sizeof(mbstate_t));
	old_n = n = strlen(s);

	while (n > 0) {
		bytesconsumed = mbrtowc(&nextchar, s, n, &state);
		if (bytesconsumed == (size_t)(-1) ||
		    bytesconsumed == (size_t)(-2)) {
			/* Something went wrong, return something reasonable */
			return old_n;
		}
		if (s[0] == '\n') {
			/*
			 * do what strlen() would do, so that caller
			 * is always right
			 */
			width++;
		} else {
			int w = wcwidth(nextchar);
			if (w > 0)
				width += w;
		}

		s += bytesconsumed, n -= bytesconsumed;
	}
	return width;
#else
	return strlen(s);
#endif
}
