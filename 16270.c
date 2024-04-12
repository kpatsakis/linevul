static Cache GetImagePixelCache(Image *image,const MagickBooleanType clone,
  ExceptionInfo *exception)
{
  CacheInfo
    *restrict cache_info;

  MagickBooleanType
    destroy,
    status;

  static MagickSizeType
    cpu_throttle = 0,
    cycles = 0,
    time_limit = 0;

  static time_t
    cache_timestamp = 0;

  status=MagickTrue;
  LockSemaphoreInfo(image->semaphore);
  if (cpu_throttle == 0)
    cpu_throttle=GetMagickResourceLimit(ThrottleResource);
  if ((cpu_throttle != MagickResourceInfinity) && ((cycles++ % 32) == 0))
    MagickDelay(cpu_throttle);
  if (time_limit == 0)
    {
      /*
        Set the expire time in seconds.
      */
      time_limit=GetMagickResourceLimit(TimeResource);
      cache_timestamp=time((time_t *) NULL);
    }
  if ((time_limit != MagickResourceInfinity) &&
      ((MagickSizeType) (time((time_t *) NULL)-cache_timestamp) >= time_limit))
     {
#if defined(ECANCELED)
       errno=ECANCELED;
#endif
       ThrowFatalException(ResourceLimitFatalError,"TimeLimitExceeded");
     }
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  destroy=MagickFalse;
  if ((cache_info->reference_count > 1) || (cache_info->mode == ReadMode))
    {
      LockSemaphoreInfo(cache_info->semaphore);
      if ((cache_info->reference_count > 1) || (cache_info->mode == ReadMode))
        {
          CacheInfo
            *clone_info;

          Image
            clone_image;

          /*
            Clone pixel cache.
          */
          clone_image=(*image);
          clone_image.semaphore=AllocateSemaphoreInfo();
          clone_image.reference_count=1;
          clone_image.cache=ClonePixelCache(cache_info);
          clone_info=(CacheInfo *) clone_image.cache;
          status=OpenPixelCache(&clone_image,IOMode,exception);
          if (status != MagickFalse)
            {
              if (clone != MagickFalse)
                status=ClonePixelCacheRepository(clone_info,cache_info,
                  exception);
              if (status != MagickFalse)
                {
                  if (cache_info->reference_count == 1)
                    cache_info->nexus_info=(NexusInfo **) NULL;
                  destroy=MagickTrue;
                  image->cache=clone_image.cache;
                }
            }
          DestroySemaphoreInfo(&clone_image.semaphore);
        }
      UnlockSemaphoreInfo(cache_info->semaphore);
    }
  if (destroy != MagickFalse)
    cache_info=(CacheInfo *) DestroyPixelCache(cache_info);
  if (status != MagickFalse)
    {
      /*
        Ensure the image matches the pixel cache morphology.
      */
      image->type=UndefinedType;
      if (ValidatePixelCacheMorphology(image) == MagickFalse)
        {
          status=OpenPixelCache(image,IOMode,exception);
          cache_info=(CacheInfo *) image->cache;
          if (cache_info->type == DiskCache)
            (void) ClosePixelCacheOnDisk(cache_info);
        }
    }
  UnlockSemaphoreInfo(image->semaphore);
  if (status == MagickFalse)
    return((Cache) NULL);
  return(image->cache);
}