void jpc_ns_fwdlift_colres(jpc_fix_t *a, int numrows, int numcols,
  int stride, int parity)
{

	jpc_fix_t *lptr;
	jpc_fix_t *hptr;
	register jpc_fix_t *lptr2;
	register jpc_fix_t *hptr2;
	register int n;
	register int i;
	int llen;

	llen = (numrows + 1 - parity) >> 1;

	if (numrows > 1) {

		/* Apply the first lifting step. */
		lptr = &a[0];
		hptr = &a[llen * stride];
		if (parity) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(hptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * ALPHA),
				  lptr2[0]));
				++hptr2;
				++lptr2;
			}
			hptr += stride;
		}
		n = numrows - llen - parity - (parity == (numrows & 1));
		while (n-- > 0) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(hptr2[0], jpc_fix_mul(jpc_dbltofix(ALPHA),
				  jpc_fix_add(lptr2[0], lptr2[stride])));
				++lptr2;
				++hptr2;
			}
			hptr += stride;
			lptr += stride;
		}
		if (parity == (numrows & 1)) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(hptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * ALPHA),
				  lptr2[0]));
				++lptr2;
				++hptr2;
			}
		}

		/* Apply the second lifting step. */
		lptr = &a[0];
		hptr = &a[llen * stride];
		if (!parity) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(lptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * BETA),
				  hptr2[0]));
				++lptr2;
				++hptr2;
			}
			lptr += stride;
		}
		n = llen - (!parity) - (parity != (numrows & 1));
		while (n-- > 0) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(lptr2[0], jpc_fix_mul(jpc_dbltofix(BETA),
				  jpc_fix_add(hptr2[0], hptr2[stride])));
				++lptr2;
				++hptr2;
			}
			lptr += stride;
			hptr += stride;
		}
		if (parity != (numrows & 1)) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(lptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * BETA),
				  hptr2[0]));
				++lptr2;
				++hptr2;
			}
		}

		/* Apply the third lifting step. */
		lptr = &a[0];
		hptr = &a[llen * stride];
		if (parity) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(hptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * GAMMA),
				  lptr2[0]));
				++hptr2;
				++lptr2;
			}
			hptr += stride;
		}
		n = numrows - llen - parity - (parity == (numrows & 1));
		while (n-- > 0) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(hptr2[0], jpc_fix_mul(jpc_dbltofix(GAMMA),
				  jpc_fix_add(lptr2[0], lptr2[stride])));
				++lptr2;
				++hptr2;
			}
			hptr += stride;
			lptr += stride;
		}
		if (parity == (numrows & 1)) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(hptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * GAMMA),
				  lptr2[0]));
				++lptr2;
				++hptr2;
			}
		}

		/* Apply the fourth lifting step. */
		lptr = &a[0];
		hptr = &a[llen * stride];
		if (!parity) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(lptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * DELTA),
				  hptr2[0]));
				++lptr2;
				++hptr2;
			}
			lptr += stride;
		}
		n = llen - (!parity) - (parity != (numrows & 1));
		while (n-- > 0) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(lptr2[0], jpc_fix_mul(jpc_dbltofix(DELTA),
				  jpc_fix_add(hptr2[0], hptr2[stride])));
				++lptr2;
				++hptr2;
			}
			lptr += stride;
			hptr += stride;
		}
		if (parity != (numrows & 1)) {
			lptr2 = lptr;
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				jpc_fix_pluseq(lptr2[0], jpc_fix_mul(jpc_dbltofix(2.0 * DELTA),
				  hptr2[0]));
				++lptr2;
				++hptr2;
			}
		}

		/* Apply the scaling step. */
#if defined(WT_DOSCALE)
		lptr = &a[0];
		n = llen;
		while (n-- > 0) {
			lptr2 = lptr;
			for (i = 0; i < numcols; ++i) {
				lptr2[0] = jpc_fix_mul(lptr2[0], jpc_dbltofix(LGAIN));
				++lptr2;
			}
			lptr += stride;
		}
		hptr = &a[llen * stride];
		n = numrows - llen;
		while (n-- > 0) {
			hptr2 = hptr;
			for (i = 0; i < numcols; ++i) {
				hptr2[0] = jpc_fix_mul(hptr2[0], jpc_dbltofix(HGAIN));
				++hptr2;
			}
			hptr += stride;
		}
#endif

	} else {

#if defined(WT_LENONE)
		if (parity) {
			lptr2 = &a[0];
			for (i = 0; i < numcols; ++i) {
				lptr2[0] = jpc_fix_asl(lptr2[0], 1);
				++lptr2;
			}
		}
#endif

	}

}
