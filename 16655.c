static int parse_sliteral(char **c, char **dst)
{
	struct token t;
	char *s = *c;

	get_token(c, &t, L_SLITERAL);

	if (t.type != T_STRING) {
		printf("Expected string literal: %.*s\n", (int)(*c - s), s);
		return -EINVAL;
	}

	*dst = t.val;

	return 1;
}
