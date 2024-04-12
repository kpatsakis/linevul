xsltFreeStackElemList(xsltStackElemPtr elem) {
    xsltStackElemPtr next;

    while (elem != NULL) {
	next = elem->next;
	xsltFreeStackElem(elem);
	elem = next;
    }
}
