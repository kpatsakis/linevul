xmlXPtrRangeCheckOrder(xmlXPathObjectPtr range) {
    int tmp;
    xmlNodePtr tmp2;
    if (range == NULL)
	return;
    if (range->type != XPATH_RANGE)
	return;
    if (range->user2 == NULL)
	return;
    tmp = xmlXPtrCmpPoints(range->user, range->index,
	                     range->user2, range->index2);
    if (tmp == -1) {
	tmp2 = range->user;
	range->user = range->user2;
	range->user2 = tmp2;
	tmp = range->index;
	range->index = range->index2;
	range->index2 = tmp;
    }
}
