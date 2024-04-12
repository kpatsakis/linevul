_peekURL(int only_img)
{

    Anchor *a;
    ParsedURL pu;
    static Str s = NULL;
#ifdef USE_M17N
    static Lineprop *p = NULL;
    Lineprop *pp;
#endif
    static int offset = 0, n;

    if (Currentbuf->firstLine == NULL)
	return;
    if (CurrentKey == prev_key && s != NULL) {
	if (s->length - offset >= COLS)
	    offset++;
	else if (s->length <= offset)	/* bug ? */
	    offset = 0;
	goto disp;
    }
    else {
	offset = 0;
    }
    s = NULL;
    a = (only_img ? NULL : retrieveCurrentAnchor(Currentbuf));
    if (a == NULL) {
	a = (only_img ? NULL : retrieveCurrentForm(Currentbuf));
	if (a == NULL) {
	    a = retrieveCurrentImg(Currentbuf);
	    if (a == NULL)
		return;
	}
	else
	    s = Strnew_charp(form2str((FormItemList *)a->url));
    }
    if (s == NULL) {
	parseURL2(a->url, &pu, baseURL(Currentbuf));
	s = parsedURL2Str(&pu);
    }
    if (DecodeURL)
	s = Strnew_charp(url_decode2(s->ptr, Currentbuf));
#ifdef USE_M17N
    s = checkType(s, &pp, NULL);
    p = NewAtom_N(Lineprop, s->length);
    bcopy((void *)pp, (void *)p, s->length * sizeof(Lineprop));
#endif
  disp:
    n = searchKeyNum();
    if (n > 1 && s->length > (n - 1) * (COLS - 1))
	offset = (n - 1) * (COLS - 1);
#ifdef USE_M17N
    while (offset < s->length && p[offset] & PC_WCHAR2)
	offset++;
#endif
    disp_message_nomouse(&s->ptr[offset], TRUE);
}
