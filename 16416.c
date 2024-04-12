const char *string_of_NPReason(int reason)
{
  const char *str;

  switch ((NPReason)reason) {
#define _(VAL) case VAL: str = #VAL; break;
    _(NPRES_DONE);
    _(NPRES_NETWORK_ERR);
    _(NPRES_USER_BREAK);
#undef _
  default:
	str = "<unknown reason>";
	break;
  }

  return str;
}
