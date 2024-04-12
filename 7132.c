sn_array_start(void *state)
{
	StripnullState *_state = (StripnullState *) state;

	appendStringInfoCharMacro(_state->strval, '[');
}
