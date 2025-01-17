ikev1_print(netdissect_options *ndo,
	    const u_char *bp,  u_int length,
	    const u_char *bp2, struct isakmp *base)
{
	const struct isakmp *p;
	const u_char *ep;
	u_char np;
	int i;
	int phase;

	p = (const struct isakmp *)bp;
	ep = ndo->ndo_snapend;

	phase = (EXTRACT_32BITS(base->msgid) == 0) ? 1 : 2;
	if (phase == 1)
		ND_PRINT((ndo," phase %d", phase));
	else
		ND_PRINT((ndo," phase %d/others", phase));

	i = cookie_find(&base->i_ck);
	if (i < 0) {
		if (iszero((const u_char *)&base->r_ck, sizeof(base->r_ck))) {
			/* the first packet */
			ND_PRINT((ndo," I"));
			if (bp2)
				cookie_record(&base->i_ck, bp2);
		} else
			ND_PRINT((ndo," ?"));
	} else {
		if (bp2 && cookie_isinitiator(i, bp2))
			ND_PRINT((ndo," I"));
		else if (bp2 && cookie_isresponder(i, bp2))
			ND_PRINT((ndo," R"));
		else
			ND_PRINT((ndo," ?"));
	}

	ND_PRINT((ndo," %s", ETYPESTR(base->etype)));
	if (base->flags) {
		ND_PRINT((ndo,"[%s%s]", base->flags & ISAKMP_FLAG_E ? "E" : "",
			  base->flags & ISAKMP_FLAG_C ? "C" : ""));
	}

	if (ndo->ndo_vflag) {
		const struct isakmp_gen *ext;

		ND_PRINT((ndo,":"));

		/* regardless of phase... */
		if (base->flags & ISAKMP_FLAG_E) {
			/*
			 * encrypted, nothing we can do right now.
			 * we hope to decrypt the packet in the future...
			 */
			ND_PRINT((ndo," [encrypted %s]", NPSTR(base->np)));
			goto done;
		}

		CHECKLEN(p + 1, base->np);
		np = base->np;
		ext = (const struct isakmp_gen *)(p + 1);
		ikev1_sub_print(ndo, np, ext, ep, phase, 0, 0, 0);
	}

done:
	if (ndo->ndo_vflag) {
		if (ntohl(base->len) != length) {
			ND_PRINT((ndo," (len mismatch: isakmp %u/ip %u)",
				  (uint32_t)ntohl(base->len), length));
		}
	}
}
