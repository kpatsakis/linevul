moveTab(TabBuffer * t, TabBuffer * t2, int right)
{
    if (t2 == NO_TABBUFFER)
	t2 = FirstTab;
    if (!t || !t2 || t == t2 || t == NO_TABBUFFER)
	return;
    if (t->prevTab) {
	if (t->nextTab)
	    t->nextTab->prevTab = t->prevTab;
	else
	    LastTab = t->prevTab;
	t->prevTab->nextTab = t->nextTab;
    }
    else {
	t->nextTab->prevTab = NULL;
	FirstTab = t->nextTab;
    }
    if (right) {
	t->nextTab = t2->nextTab;
	t->prevTab = t2;
	if (t2->nextTab)
	    t2->nextTab->prevTab = t;
	else
	    LastTab = t;
	t2->nextTab = t;
    }
    else {
	t->prevTab = t2->prevTab;
	t->nextTab = t2;
	if (t2->prevTab)
	    t2->prevTab->nextTab = t;
	else
	    FirstTab = t;
	t2->prevTab = t;
    }
    displayBuffer(Currentbuf, B_FORCE_REDRAW);
}
