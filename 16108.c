each_array_start(void *state)
{
	EachState  *_state = (EachState *) state;

	/* json structure check */
	if (_state->lex->lex_level == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot deconstruct an array as an object")));
}
