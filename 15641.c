static void eol_or_eof(char **c)
{
	while (**c && **c != '\n')
		(*c)++;
}
