static MagickBooleanType ForwardFourier(const FourierInfo *fourier_info,
  Image *image,double *magnitude,double *phase,ExceptionInfo *exception)
{
  CacheView
    *magnitude_view,
    *phase_view;

  double
    *magnitude_pixels,
    *phase_pixels;

  Image
    *magnitude_image,
    *phase_image;

  MagickBooleanType
    status;

  MemoryInfo
    *magnitude_info,
    *phase_info;

  register IndexPacket
    *indexes;

  register PixelPacket
    *q;

  register ssize_t
    x;

  ssize_t
    i,
    y;

  magnitude_image=GetFirstImageInList(image);
  phase_image=GetNextImageInList(image);
  if (phase_image == (Image *) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),ImageError,
        "ImageSequenceRequired","`%s'",image->filename);
      return(MagickFalse);
    }
  /*
    Create "Fourier Transform" image from constituent arrays.
  */
  magnitude_info=AcquireVirtualMemory((size_t) fourier_info->width,
    fourier_info->height*sizeof(*magnitude_pixels));
  phase_info=AcquireVirtualMemory((size_t) fourier_info->width,
    fourier_info->height*sizeof(*phase_pixels));
  if ((magnitude_info == (MemoryInfo *) NULL) ||
      (phase_info == (MemoryInfo *) NULL))
    {
      if (phase_info != (MemoryInfo *) NULL)
        phase_info=RelinquishVirtualMemory(phase_info);
      if (magnitude_info != (MemoryInfo *) NULL)
        magnitude_info=RelinquishVirtualMemory(magnitude_info);
      (void) ThrowMagickException(exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",image->filename);
      return(MagickFalse);
    }
  magnitude_pixels=(double *) GetVirtualMemoryBlob(magnitude_info);
  (void) memset(magnitude_pixels,0,fourier_info->width*
    fourier_info->height*sizeof(*magnitude_pixels));
  phase_pixels=(double *) GetVirtualMemoryBlob(phase_info);
  (void) memset(phase_pixels,0,fourier_info->width*
    fourier_info->height*sizeof(*phase_pixels));
  status=ForwardQuadrantSwap(fourier_info->width,fourier_info->height,
    magnitude,magnitude_pixels);
  if (status != MagickFalse)
    status=ForwardQuadrantSwap(fourier_info->width,fourier_info->height,phase,
      phase_pixels);
  CorrectPhaseLHS(fourier_info->width,fourier_info->height,phase_pixels);
  if (fourier_info->modulus != MagickFalse)
    {
      i=0L;
      for (y=0L; y < (ssize_t) fourier_info->height; y++)
        for (x=0L; x < (ssize_t) fourier_info->width; x++)
        {
          phase_pixels[i]/=(2.0*MagickPI);
          phase_pixels[i]+=0.5;
          i++;
        }
    }
  magnitude_view=AcquireAuthenticCacheView(magnitude_image,exception);
  i=0L;
  for (y=0L; y < (ssize_t) fourier_info->height; y++)
  {
    q=GetCacheViewAuthenticPixels(magnitude_view,0L,y,fourier_info->width,1UL,
      exception);
    if (q == (PixelPacket *) NULL)
      break;
    indexes=GetCacheViewAuthenticIndexQueue(magnitude_view);
    for (x=0L; x < (ssize_t) fourier_info->width; x++)
    {
      switch (fourier_info->channel)
      {
        case RedChannel:
        default:
        {
          SetPixelRed(q,ClampToQuantum(QuantumRange*magnitude_pixels[i]));
          break;
        }
        case GreenChannel:
        {
          SetPixelGreen(q,ClampToQuantum(QuantumRange*magnitude_pixels[i]));
          break;
        }
        case BlueChannel:
        {
          SetPixelBlue(q,ClampToQuantum(QuantumRange*magnitude_pixels[i]));
          break;
        }
        case OpacityChannel:
        {
          SetPixelOpacity(q,ClampToQuantum(QuantumRange*magnitude_pixels[i]));
          break;
        }
        case IndexChannel:
        {
          SetPixelIndex(indexes+x,ClampToQuantum(QuantumRange*
            magnitude_pixels[i]));
          break;
        }
        case GrayChannels:
        {
          SetPixelGray(q,ClampToQuantum(QuantumRange*magnitude_pixels[i]));
          break;
        }
      }
      i++;
      q++;
    }
    status=SyncCacheViewAuthenticPixels(magnitude_view,exception);
    if (status == MagickFalse)
      break;
  }
  magnitude_view=DestroyCacheView(magnitude_view);
  i=0L;
  phase_view=AcquireAuthenticCacheView(phase_image,exception);
  for (y=0L; y < (ssize_t) fourier_info->height; y++)
  {
    q=GetCacheViewAuthenticPixels(phase_view,0L,y,fourier_info->width,1UL,
      exception);
    if (q == (PixelPacket *) NULL)
      break;
    indexes=GetCacheViewAuthenticIndexQueue(phase_view);
    for (x=0L; x < (ssize_t) fourier_info->width; x++)
    {
      switch (fourier_info->channel)
      {
        case RedChannel:
        default:
        {
          SetPixelRed(q,ClampToQuantum(QuantumRange*phase_pixels[i]));
          break;
        }
        case GreenChannel:
        {
          SetPixelGreen(q,ClampToQuantum(QuantumRange*phase_pixels[i]));
          break;
        }
        case BlueChannel:
        {
          SetPixelBlue(q,ClampToQuantum(QuantumRange*phase_pixels[i]));
          break;
        }
        case OpacityChannel:
        {
          SetPixelOpacity(q,ClampToQuantum(QuantumRange*phase_pixels[i]));
          break;
        }
        case IndexChannel:
        {
          SetPixelIndex(indexes+x,ClampToQuantum(QuantumRange*phase_pixels[i]));
          break;
        }
        case GrayChannels:
        {
          SetPixelGray(q,ClampToQuantum(QuantumRange*phase_pixels[i]));
          break;
        }
      }
      i++;
      q++;
    }
    status=SyncCacheViewAuthenticPixels(phase_view,exception);
    if (status == MagickFalse)
      break;
   }
  phase_view=DestroyCacheView(phase_view);
  phase_info=RelinquishVirtualMemory(phase_info);
  magnitude_info=RelinquishVirtualMemory(magnitude_info);
  return(status);
}