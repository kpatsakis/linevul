_nextA(int visited)
{
    HmarkerList *hl = Currentbuf->hmarklist;
    BufferPoint *po;
    Anchor *an, *pan;
    int i, x, y, n = searchKeyNum();
    ParsedURL url;

    if (Currentbuf->firstLine == NULL)
	return;
    if (!hl || hl->nmark == 0)
	return;

    an = retrieveCurrentAnchor(Currentbuf);
    if (visited != TRUE && an == NULL)
	an = retrieveCurrentForm(Currentbuf);

    y = Currentbuf->currentLine->linenumber;
    x = Currentbuf->pos;

    if (visited == TRUE) {
	n = hl->nmark;
    }

    for (i = 0; i < n; i++) {
	pan = an;
	if (an && an->hseq >= 0) {
	    int hseq = an->hseq + 1;
	    do {
		if (hseq >= hl->nmark) {
		    if (visited == TRUE)
			return;
		    an = pan;
		    goto _end;
		}
		po = &hl->marks[hseq];
		an = retrieveAnchor(Currentbuf->href, po->line, po->pos);
		if (visited != TRUE && an == NULL)
		    an = retrieveAnchor(Currentbuf->formitem, po->line,
					po->pos);
		hseq++;
		if (visited == TRUE && an) {
		    parseURL2(an->url, &url, baseURL(Currentbuf));
		    if (getHashHist(URLHist, parsedURL2Str(&url)->ptr)) {
			goto _end;
		    }
		}
	    } while (an == NULL || an == pan);
	}
	else {
	    an = closest_next_anchor(Currentbuf->href, NULL, x, y);
	    if (visited != TRUE)
		an = closest_next_anchor(Currentbuf->formitem, an, x, y);
	    if (an == NULL) {
		if (visited == TRUE)
		    return;
		an = pan;
		break;
	    }
	    x = an->start.pos;
	    y = an->start.line;
	    if (visited == TRUE) {
		parseURL2(an->url, &url, baseURL(Currentbuf));
		if (getHashHist(URLHist, parsedURL2Str(&url)->ptr)) {
		    goto _end;
		}
	    }
	}
    }
    if (visited == TRUE)
	return;

  _end:
    if (an == NULL || an->hseq < 0)
	return;
    po = &hl->marks[an->hseq];
    gotoLine(Currentbuf, po->line);
    Currentbuf->pos = po->pos;
    arrangeCursor(Currentbuf);
    displayBuffer(Currentbuf, B_NORMAL);
}
