populate_recordset_scalar(void *state, char *token, JsonTokenType tokentype)
{
	PopulateRecordsetState *_state = (PopulateRecordsetState *) state;

	if (_state->lex->lex_level == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot call %s on a scalar",
						_state->function_name)));

	if (_state->lex->lex_level == 2)
		_state->saved_scalar = token;
}
