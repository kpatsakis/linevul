escdmap(char c)
{
    int d;
    d = (int)c - (int)'0';
    c = getch();
    if (IS_DIGIT(c)) {
	d = d * 10 + (int)c - (int)'0';
	c = getch();
    }
    if (c == '~')
	escKeyProc((int)d, K_ESCD, EscDKeymap);
}
