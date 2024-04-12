numTab(int n)
{
    TabBuffer *tab;
    int i;

    if (n == 0)
	return CurrentTab;
    if (n == 1)
	return FirstTab;
    if (nTab <= 1)
	return NULL;
    for (tab = FirstTab, i = 1; tab && i < n; tab = tab->nextTab, i++) ;
    return tab;
}
