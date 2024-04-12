MagickExport MagickBooleanType GetOneVirtualMagickPixel(const Image *image,
  const ssize_t x,const ssize_t y,MagickPixelPacket *pixel,
  ExceptionInfo *exception)
{
  CacheInfo
    *magick_restrict cache_info;

  const int
    id = GetOpenMPThreadId();

  register const IndexPacket
    *magick_restrict indexes;

  register const PixelPacket
    *magick_restrict pixels;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  assert(id < (int) cache_info->number_threads);
  pixels=GetVirtualPixelsFromNexus(image,GetPixelCacheVirtualMethod(image),x,y,
    1UL,1UL,cache_info->nexus_info[id],exception);
  GetMagickPixelPacket(image,pixel);
  if (pixels == (const PixelPacket *) NULL)
    return(MagickFalse);
  indexes=GetVirtualIndexesFromNexus(cache_info,cache_info->nexus_info[id]);
  SetMagickPixelPacket(image,pixels,indexes,pixel);
  return(MagickTrue);
}
