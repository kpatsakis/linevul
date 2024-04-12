next_nonnull_line(Line *line)
{
    Line *l;

    for (l = line; l != NULL && l->len == 0; l = l->next) ;

    if (l == NULL || l->len == 0)
	return -1;

    Currentbuf->currentLine = l;
    if (l != line)
	Currentbuf->pos = 0;
    return 0;
}
