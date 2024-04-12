static iw_tmpsample x_to_linear_sample(iw_tmpsample v, const struct iw_csdescr *csdescr)
{
	switch(csdescr->cstype) {
	case IW_CSTYPE_SRGB:
		return srgb_to_linear_sample(v);
	case IW_CSTYPE_LINEAR:
		return v;
	case IW_CSTYPE_GAMMA:
		return gamma_to_linear_sample(v,csdescr->gamma);
	case IW_CSTYPE_REC709:
		return rec709_to_linear_sample(v);
	}
	return srgb_to_linear_sample(v);
}
