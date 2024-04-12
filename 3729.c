EncodeDateOnly(struct tm * tm, int style, char *str, bool EuroDates)
{
	if (tm->tm_mon < 1 || tm->tm_mon > MONTHS_PER_YEAR)
		return -1;

	switch (style)
	{
		case USE_ISO_DATES:
			/* compatible with ISO date formats */
			if (tm->tm_year > 0)
				sprintf(str, "%04d-%02d-%02d",
						tm->tm_year, tm->tm_mon, tm->tm_mday);
			else
				sprintf(str, "%04d-%02d-%02d %s",
						-(tm->tm_year - 1), tm->tm_mon, tm->tm_mday, "BC");
			break;

		case USE_SQL_DATES:
			/* compatible with Oracle/Ingres date formats */
			if (EuroDates)
				sprintf(str, "%02d/%02d", tm->tm_mday, tm->tm_mon);
			else
				sprintf(str, "%02d/%02d", tm->tm_mon, tm->tm_mday);
			if (tm->tm_year > 0)
				sprintf(str + 5, "/%04d", tm->tm_year);
			else
				sprintf(str + 5, "/%04d %s", -(tm->tm_year - 1), "BC");
			break;

		case USE_GERMAN_DATES:
			/* German-style date format */
			sprintf(str, "%02d.%02d", tm->tm_mday, tm->tm_mon);
			if (tm->tm_year > 0)
				sprintf(str + 5, ".%04d", tm->tm_year);
			else
				sprintf(str + 5, ".%04d %s", -(tm->tm_year - 1), "BC");
			break;

		case USE_POSTGRES_DATES:
		default:
			/* traditional date-only style for Postgres */
			if (EuroDates)
				sprintf(str, "%02d-%02d", tm->tm_mday, tm->tm_mon);
			else
				sprintf(str, "%02d-%02d", tm->tm_mon, tm->tm_mday);
			if (tm->tm_year > 0)
				sprintf(str + 5, "-%04d", tm->tm_year);
			else
				sprintf(str + 5, "-%04d %s", -(tm->tm_year - 1), "BC");
			break;
	}

	return TRUE;
}	/* EncodeDateOnly() */
