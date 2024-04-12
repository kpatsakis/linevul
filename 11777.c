sn_array_end(void *state)
{
	StripnullState *_state = (StripnullState *) state;

	appendStringInfoCharMacro(_state->strval, ']');
}
