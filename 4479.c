static inline NPUTF8 *npidentifier_cache_get_string_copy(NPIdentifier ident)
{
  NPIdentifierInfo *npi = npidentifier_cache_lookup(ident);
  if (G_UNLIKELY(npi == NULL || npi->string_len == 0))
	return NULL;
  return NPW_MemAllocCopy(npi->string_len, npi->u.string);
}
