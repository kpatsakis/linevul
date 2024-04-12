report_parse_error(JsonParseContext ctx, JsonLexContext *lex)
{
	char	   *token;
	int			toklen;

	/* Handle case where the input ended prematurely. */
	if (lex->token_start == NULL || lex->token_type == JSON_TOKEN_END)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type json"),
				 errdetail("The input string ended unexpectedly."),
				 report_json_context(lex)));

	/* Separate out the current token. */
	toklen = lex->token_terminator - lex->token_start;
	token = palloc(toklen + 1);
	memcpy(token, lex->token_start, toklen);
	token[toklen] = '\0';

	/* Complain, with the appropriate detail message. */
	if (ctx == JSON_PARSE_END)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type json"),
				 errdetail("Expected end of input, but found \"%s\".",
						   token),
				 report_json_context(lex)));
	else
	{
		switch (ctx)
		{
			case JSON_PARSE_VALUE:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
						 errdetail("Expected JSON value, but found \"%s\".",
								   token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_STRING:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
						 errdetail("Expected string, but found \"%s\".",
								   token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_ARRAY_START:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
						 errdetail("Expected array element or \"]\", but found \"%s\".",
								   token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_ARRAY_NEXT:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
					  errdetail("Expected \",\" or \"]\", but found \"%s\".",
								token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_OBJECT_START:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
					 errdetail("Expected string or \"}\", but found \"%s\".",
							   token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_OBJECT_LABEL:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
						 errdetail("Expected \":\", but found \"%s\".",
								   token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_OBJECT_NEXT:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
					  errdetail("Expected \",\" or \"}\", but found \"%s\".",
								token),
						 report_json_context(lex)));
				break;
			case JSON_PARSE_OBJECT_COMMA:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type json"),
						 errdetail("Expected string, but found \"%s\".",
								   token),
						 report_json_context(lex)));
				break;
			default:
				elog(ERROR, "unexpected json parse state: %d", ctx);
		}
