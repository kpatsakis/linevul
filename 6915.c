exsltDateWeekInYear (const xmlChar *dateTime)
{
    exsltDateValPtr dt;
    long diy, diw, year, ret;

    if (dateTime == NULL) {
#ifdef WITH_TIME
	dt = exsltDateCurrent();
	if (dt == NULL)
#endif
	    return xmlXPathNAN;
    } else {
	dt = exsltDateParse(dateTime);
	if (dt == NULL)
	    return xmlXPathNAN;
	if ((dt->type != XS_DATETIME) && (dt->type != XS_DATE)) {
	    exsltDateFreeDate(dt);
	    return xmlXPathNAN;
	}
    }

    diy = DAY_IN_YEAR(dt->value.date.day, dt->value.date.mon,
                      dt->value.date.year);

    /*
     * Determine day-in-week (0=Sun, 1=Mon, etc.) then adjust so Monday
     * is the first day-in-week
     */
    diw = (_exsltDateDayInWeek(diy, dt->value.date.year) + 6) % 7;

    /* ISO 8601 adjustment, 3 is Thu */
    diy += (3 - diw);
    if(diy < 1) {
	year = dt->value.date.year - 1;
	if(year == 0) year--;
	diy = DAY_IN_YEAR(31, 12, year) + diy;
    } else if (diy > (long)DAY_IN_YEAR(31, 12, dt->value.date.year)) {
	diy -= DAY_IN_YEAR(31, 12, dt->value.date.year);
    }

    ret = ((diy - 1) / 7) + 1;

    exsltDateFreeDate(dt);

    return (double) ret;
}
