short *XRRConfigRates (XRRScreenConfiguration *config, int sizeID, int *nrates)
{
    short   *r = config->rates;
    int	    nents = config->nrates;

    /* Skip over the intervening rate lists */
    while (sizeID > 0 && nents > 0)
    {
	int i = (*r + 1);
	r += i;
	nents -= i;
	sizeID--;
    }
    if (!nents)
    {
	*nrates = 0;
	return NULL;
    }
    *nrates = (int) *r;
    return r + 1;
}
