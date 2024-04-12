lex_accept(JsonLexContext *lex, JsonTokenType token, char **lexeme)
{
	if (lex->token_type == token)
	{
		if (lexeme != NULL)
		{
			if (lex->token_type == JSON_TOKEN_STRING)
			{
				if (lex->strval != NULL)
					*lexeme = pstrdup(lex->strval->data);
			}
			else
			{
				int			len = (lex->token_terminator - lex->token_start);
				char	   *tokstr = palloc(len + 1);

				memcpy(tokstr, lex->token_start, len);
				tokstr[len] = '\0';
				*lexeme = tokstr;
			}
		}
		json_lex(lex);
		return true;
	}
	return false;
}
