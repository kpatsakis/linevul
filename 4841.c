int FLTIsTemporalFilterType(const char *pszValue)
{
  if (pszValue) {
    if ( strcasecmp(pszValue, "During") == 0 )
      return MS_TRUE;
  }

  return MS_FALSE;
}
