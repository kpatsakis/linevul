MagickExport const IndexPacket *GetVirtualIndexesFromNexus(const Cache cache,
  NexusInfo *nexus_info)
{
  CacheInfo
    *restrict cache_info;

  assert(cache != (Cache) NULL);
  cache_info=(CacheInfo *) cache;
  assert(cache_info->signature == MagickSignature);
  if (cache_info->storage_class == UndefinedClass)
    return((IndexPacket *) NULL);
  return(nexus_info->indexes);
}
