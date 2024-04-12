stringprep_4zi_1 (uint32_t * ucs4, size_t ucs4len, size_t maxucs4len,
		  Stringprep_profile_flags flags,
		  const Stringprep_profile * profile)
{
  int rc;

  rc = stringprep_4i (ucs4, &ucs4len, maxucs4len, flags, profile);
  if (rc != STRINGPREP_OK)
    return rc;

  if (ucs4len >= maxucs4len)
    return STRINGPREP_TOO_SMALL_BUFFER;

  ucs4[ucs4len] = 0;

  return STRINGPREP_OK;
}
