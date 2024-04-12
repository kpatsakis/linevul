static int dec(struct cstate *g, int c)
{
	if (c >= '0' && c <= '9') return c - '0';
	die(g, "invalid quantifier");
	return 0;
}
