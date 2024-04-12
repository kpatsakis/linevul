void ndp_msgra_flag_managed_set(struct ndp_msgra *msgra, bool flag_managed)
{
	if (flag_managed)
		msgra->ra->nd_ra_flags_reserved |= ND_RA_FLAG_MANAGED;
	else
		msgra->ra->nd_ra_flags_reserved &= ~ND_RA_FLAG_MANAGED;
}
