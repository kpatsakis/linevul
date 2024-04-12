_movR(int n)
{
    int i, m = searchKeyNum();
    if (Currentbuf->firstLine == NULL)
	return;
    for (i = 0; i < m; i++)
	cursorRight(Currentbuf, n);
    displayBuffer(Currentbuf, B_NORMAL);
}
