MagickExport MagickBooleanType GetOneVirtualPixel(const Image *image,
  const ssize_t x,const ssize_t y,PixelPacket *pixel,ExceptionInfo *exception)
{
  CacheInfo
    *magick_restrict cache_info;

  const int
    id = GetOpenMPThreadId();

  const PixelPacket
    *magick_restrict pixels;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  *pixel=image->background_color;
  if (cache_info->methods.get_one_virtual_pixel_from_handler !=
       (GetOneVirtualPixelFromHandler) NULL)
    return(cache_info->methods.get_one_virtual_pixel_from_handler(image,
      GetPixelCacheVirtualMethod(image),x,y,pixel,exception));
  assert(id < (int) cache_info->number_threads);
  pixels=GetVirtualPixelsFromNexus(image,GetPixelCacheVirtualMethod(image),x,y,
    1UL,1UL,cache_info->nexus_info[id],exception);
  if (pixels == (const PixelPacket *) NULL)
    return(MagickFalse);
  *pixel=(*pixels);
  return(MagickTrue);
}
