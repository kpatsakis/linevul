void jpc_ft_invlift_col(jpc_fix_t *a, int numrows, int stride, int parity)
{

	jpc_fix_t *lptr;
	jpc_fix_t *hptr;
#if 0
	register jpc_fix_t *lptr2;
	register jpc_fix_t *hptr2;
	register int i;
#endif
	register int n;
	int llen;

	llen = (numrows + 1 - parity) >> 1;

	if (numrows > 1) {

		/* Apply the first lifting step. */
		lptr = &a[0];
		hptr = &a[llen * stride];
		if (!parity) {
			lptr[0] -= jpc_fix_asr(hptr[0] + 1, 1);
			lptr += stride;
		}
		n = llen - (!parity) - (parity != (numrows & 1));
		while (n-- > 0) {
			lptr[0] -= jpc_fix_asr(hptr[0] + hptr[stride] + 2, 2);
			lptr += stride;
			hptr += stride;
		}
		if (parity != (numrows & 1)) {
			lptr[0] -= jpc_fix_asr(hptr[0] + 1, 1);
		}

		/* Apply the second lifting step. */
		lptr = &a[0];
		hptr = &a[llen * stride];
		if (parity) {
			hptr[0] += lptr[0];
			hptr += stride;
		}
		n = numrows - llen - parity - (parity == (numrows & 1));
		while (n-- > 0) {
			hptr[0] += jpc_fix_asr(lptr[0] + lptr[stride], 1);
			hptr += stride;
			lptr += stride;
		}
		if (parity == (numrows & 1)) {
			hptr[0] += lptr[0];
		}

	} else {

		if (parity) {
			lptr = &a[0];
			lptr[0] = jpc_fix_asr(lptr[0], 1);
		}

	}

}
