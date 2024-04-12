exsltDateParse (const xmlChar *dateTime)
{
    exsltDateValPtr dt;
    int ret;
    const xmlChar *cur = dateTime;

#define RETURN_TYPE_IF_VALID(t)					\
    if (IS_TZO_CHAR(*cur)) {					\
	ret = _exsltDateParseTimeZone(&(dt->value.date), &cur);	\
	if (ret == 0) {						\
	    if (*cur != 0)					\
		goto error;					\
	    dt->type = t;					\
	    return dt;						\
	}							\
    }

    if (dateTime == NULL)
	return NULL;

    if ((*cur != '-') && (*cur < '0') && (*cur > '9'))
	return NULL;

    dt = exsltDateCreateDate(EXSLT_UNKNOWN);
    if (dt == NULL)
	return NULL;

    if ((cur[0] == '-') && (cur[1] == '-')) {
	/*
	 * It's an incomplete date (xs:gMonthDay, xs:gMonth or
	 * xs:gDay)
	 */
	cur += 2;

	/* is it an xs:gDay? */
	if (*cur == '-') {
	  ++cur;
	    ret = _exsltDateParseGDay(&(dt->value.date), &cur);
	    if (ret != 0)
		goto error;

	    RETURN_TYPE_IF_VALID(XS_GDAY);

	    goto error;
	}

	/*
	 * it should be an xs:gMonthDay or xs:gMonth
	 */
	ret = _exsltDateParseGMonth(&(dt->value.date), &cur);
	if (ret != 0)
	    goto error;

	if (*cur != '-')
	    goto error;
	cur++;

	/* is it an xs:gMonth? */
	if (*cur == '-') {
	    cur++;
	    RETURN_TYPE_IF_VALID(XS_GMONTH);
	    goto error;
	}

	/* it should be an xs:gMonthDay */
	ret = _exsltDateParseGDay(&(dt->value.date), &cur);
	if (ret != 0)
	    goto error;

	RETURN_TYPE_IF_VALID(XS_GMONTHDAY);

	goto error;
    }

    /*
     * It's a right-truncated date or an xs:time.
     * Try to parse an xs:time then fallback on right-truncated dates.
     */
    if ((*cur >= '0') && (*cur <= '9')) {
	ret = _exsltDateParseTime(&(dt->value.date), &cur);
	if (ret == 0) {
	    /* it's an xs:time */
	    RETURN_TYPE_IF_VALID(XS_TIME);
	}
    }

    /* fallback on date parsing */
    cur = dateTime;

    ret = _exsltDateParseGYear(&(dt->value.date), &cur);
    if (ret != 0)
	goto error;

    /* is it an xs:gYear? */
    RETURN_TYPE_IF_VALID(XS_GYEAR);

    if (*cur != '-')
	goto error;
    cur++;

    ret = _exsltDateParseGMonth(&(dt->value.date), &cur);
    if (ret != 0)
	goto error;

    /* is it an xs:gYearMonth? */
    RETURN_TYPE_IF_VALID(XS_GYEARMONTH);

    if (*cur != '-')
	goto error;
    cur++;

    ret = _exsltDateParseGDay(&(dt->value.date), &cur);
    if ((ret != 0) || !VALID_DATE((&(dt->value.date))))
	goto error;

    /* is it an xs:date? */
    RETURN_TYPE_IF_VALID(XS_DATE);

    if (*cur != 'T')
	goto error;
    cur++;

    /* it should be an xs:dateTime */
    ret = _exsltDateParseTime(&(dt->value.date), &cur);
    if (ret != 0)
	goto error;

    ret = _exsltDateParseTimeZone(&(dt->value.date), &cur);
    if ((ret != 0) || (*cur != 0) || !VALID_DATETIME((&(dt->value.date))))
	goto error;

    dt->type = XS_DATETIME;

    return dt;

error:
    if (dt != NULL)
	exsltDateFreeDate(dt);
    return NULL;
}
