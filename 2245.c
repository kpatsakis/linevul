MagickExport MagickBooleanType SyncAuthenticPixelCacheNexus(Image *image,
  NexusInfo *restrict nexus_info,ExceptionInfo *exception)
{
  CacheInfo
    *restrict cache_info;

  MagickBooleanType
    status;

  /*
    Transfer pixels to the cache.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->cache == (Cache) NULL)
    ThrowBinaryException(CacheError,"PixelCacheIsNotOpen",image->filename);
  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  if (cache_info->type == UndefinedCache)
    return(MagickFalse);
  if ((image->storage_class == DirectClass) &&
      (image->clip_mask != (Image *) NULL) &&
      (ClipPixelCacheNexus(image,nexus_info,exception) == MagickFalse))
    return(MagickFalse);
  if ((image->storage_class == DirectClass) &&
      (image->mask != (Image *) NULL) &&
      (MaskPixelCacheNexus(image,nexus_info,exception) == MagickFalse))
    return(MagickFalse);
  if (nexus_info->authentic_pixel_cache != MagickFalse)
    {
      image->taint=MagickTrue;
      return(MagickTrue);
    }
  assert(cache_info->signature == MagickSignature);
  status=WritePixelCachePixels(cache_info,nexus_info,exception);
  if ((cache_info->active_index_channel != MagickFalse) &&
      (WritePixelCacheIndexes(cache_info,nexus_info,exception) == MagickFalse))
    return(MagickFalse);
  if (status != MagickFalse)
    image->taint=MagickTrue;
  return(status);
}
