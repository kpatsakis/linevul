leap_month(
	u_long	sec		/* current NTP second */
	)
{
	int	     leap;
	int32	     year, month;
	u_int32	     ndays;
	ntpcal_split tmp;
	vint64	     tvl;

	/* --*-- expand time and split to days */
	tvl   = ntpcal_ntp_to_ntp(sec, NULL);
	tmp   = ntpcal_daysplit(&tvl);
	/* --*-- split to years and days in year */
	tmp   = ntpcal_split_eradays(tmp.hi + DAY_NTP_STARTS - 1, &leap);
	year  = tmp.hi;
	/* --*-- split days of year to month */
	tmp   = ntpcal_split_yeardays(tmp.lo, leap);
	month = tmp.hi;
	/* --*-- get nominal start of next month */
	ndays = ntpcal_edate_to_eradays(year, month+1, 0) + 1 - DAY_NTP_STARTS;
	
	return (u_int32)(ndays*SECSPERDAY - sec);
}
