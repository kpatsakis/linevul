static size_t parse_mb_loc(unsigned *wc, const char *ptr, const char *end)
{
	wchar_t wchar;
	size_t consumed = 0;
#if defined(HAVE_MBRTOWC)
	mbstate_t ps;

	memset(&ps, 0, sizeof(ps));
	consumed = mbrtowc(&wchar, ptr, end - ptr, &ps);
#elif defined(HAVE_MBTOWC)
	consumed = mbtowc(&wchar, ptr, end - ptr);
#endif

	if (!consumed || consumed == (size_t) -1) {
		return 0;
	}

	if (wc) {
		*wc = wchar;
	}
	return consumed;
}
