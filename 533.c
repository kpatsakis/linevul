_gdScalePass(const gdImagePtr pSrc, const unsigned int src_len,
             const gdImagePtr pDst, const unsigned int dst_len,
             const unsigned int num_lines,
             const gdAxis axis)
{
	unsigned int line_ndx;
	LineContribType * contrib;

    /* Same dim, just copy it. */
    assert(dst_len != src_len); // TODO: caller should handle this.

	contrib = _gdContributionsCalc(dst_len, src_len,
                                   (double)dst_len / (double)src_len,
                                   pSrc->interpolation);
	if (contrib == NULL) {
		return 0;
	}

	/* Scale each line */
    for (line_ndx = 0; line_ndx < num_lines; line_ndx++) {
        _gdScaleOneAxis(pSrc, pDst, dst_len, line_ndx, contrib, axis);
	}
	_gdContributionsFree (contrib);
    return 1;
}/* _gdScalePass*/
