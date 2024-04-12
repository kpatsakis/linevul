MagickExport const PixelPacket *GetVirtualPixelsFromNexus(const Image *image,
  const VirtualPixelMethod virtual_pixel_method,const ssize_t x,const ssize_t y,
  const size_t columns,const size_t rows,NexusInfo *nexus_info,
  ExceptionInfo *exception)
{
  CacheInfo
    *magick_restrict cache_info;

  IndexPacket
    virtual_index;

  MagickOffsetType
    offset;

  MagickSizeType
    length,
    number_pixels;

  NexusInfo
    **magick_restrict virtual_nexus;

  PixelPacket
    *magick_restrict pixels,
    virtual_pixel;

  RectangleInfo
    region;

  register const IndexPacket
    *magick_restrict virtual_indexes;

  register const PixelPacket
    *magick_restrict p;

  register IndexPacket
    *magick_restrict indexes;

  register PixelPacket
    *magick_restrict q;

  register ssize_t
    u,
    v;

  /*
    Acquire pixels.
  */
  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(image->cache != (Cache) NULL);
  cache_info=(CacheInfo *) image->cache;
  assert(cache_info->signature == MagickSignature);
  if (cache_info->type == UndefinedCache)
    return((const PixelPacket *) NULL);
  region.x=x;
  region.y=y;
  region.width=columns;
  region.height=rows;
  pixels=SetPixelCacheNexusPixels(cache_info,ReadMode,&region,
    (image->clip_mask != (Image *) NULL) || (image->mask != (Image *) NULL) ?
    MagickTrue : MagickFalse,nexus_info,exception);
  if (pixels == (PixelPacket *) NULL)
    return((const PixelPacket *) NULL);
  offset=(MagickOffsetType) nexus_info->region.y*cache_info->columns+
    nexus_info->region.x;
  length=(MagickSizeType) (nexus_info->region.height-1L)*cache_info->columns+
    nexus_info->region.width-1L;
  number_pixels=(MagickSizeType) cache_info->columns*cache_info->rows;
  if ((offset >= 0) && (((MagickSizeType) offset+length) < number_pixels))
    if ((x >= 0) && ((ssize_t) (x+columns) <= (ssize_t) cache_info->columns) &&
        (y >= 0) && ((ssize_t) (y+rows) <= (ssize_t) cache_info->rows))
      {
        MagickBooleanType
          status;

        /*
          Pixel request is inside cache extents.
        */
        if (nexus_info->authentic_pixel_cache != MagickFalse)
          return(pixels);
        status=ReadPixelCachePixels(cache_info,nexus_info,exception);
        if (status == MagickFalse)
          return((const PixelPacket *) NULL);
        if ((cache_info->storage_class == PseudoClass) ||
            (cache_info->colorspace == CMYKColorspace))
          {
            status=ReadPixelCacheIndexes(cache_info,nexus_info,exception);
            if (status == MagickFalse)
              return((const PixelPacket *) NULL);
          }
        return(pixels);
      }
  /*
    Pixel request is outside cache extents.
  */
  q=pixels;
  indexes=nexus_info->indexes;
  virtual_nexus=AcquirePixelCacheNexus(1);
  if (virtual_nexus == (NexusInfo **) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),CacheError,
        "UnableToGetCacheNexus","`%s'",image->filename);
      return((const PixelPacket *) NULL);
    }
  switch (virtual_pixel_method)
  {
    case BlackVirtualPixelMethod:
    {
      SetPixelRed(&virtual_pixel,0);
      SetPixelGreen(&virtual_pixel,0);
      SetPixelBlue(&virtual_pixel,0);
      SetPixelOpacity(&virtual_pixel,OpaqueOpacity);
      break;
    }
    case GrayVirtualPixelMethod:
    {
      SetPixelRed(&virtual_pixel,QuantumRange/2);
      SetPixelGreen(&virtual_pixel,QuantumRange/2);
      SetPixelBlue(&virtual_pixel,QuantumRange/2);
      SetPixelOpacity(&virtual_pixel,OpaqueOpacity);
      break;
    }
    case TransparentVirtualPixelMethod:
    {
      SetPixelRed(&virtual_pixel,0);
      SetPixelGreen(&virtual_pixel,0);
      SetPixelBlue(&virtual_pixel,0);
      SetPixelOpacity(&virtual_pixel,TransparentOpacity);
      break;
    }
    case MaskVirtualPixelMethod:
    case WhiteVirtualPixelMethod:
    {
      SetPixelRed(&virtual_pixel,QuantumRange);
      SetPixelGreen(&virtual_pixel,QuantumRange);
      SetPixelBlue(&virtual_pixel,QuantumRange);
      SetPixelOpacity(&virtual_pixel,OpaqueOpacity);
      break;
    }
    default:
    {
      virtual_pixel=image->background_color;
      break;
    }
  }
  virtual_index=0;
  for (v=0; v < (ssize_t) rows; v++)
  {
    ssize_t
      y_offset;

    y_offset=y+v;
    if ((virtual_pixel_method == EdgeVirtualPixelMethod) ||
        (virtual_pixel_method == UndefinedVirtualPixelMethod))
      y_offset=EdgeY(y_offset,cache_info->rows);
    for (u=0; u < (ssize_t) columns; u+=length)
    {
      ssize_t
        x_offset;

      x_offset=x+u;
      length=(MagickSizeType) MagickMin(cache_info->columns-x_offset,columns-u);
      if (((x_offset < 0) || (x_offset >= (ssize_t) cache_info->columns)) ||
          ((y_offset < 0) || (y_offset >= (ssize_t) cache_info->rows)) ||
          (length == 0))
        {
          MagickModulo
            x_modulo,
            y_modulo;

          /*
            Transfer a single pixel.
          */
          length=(MagickSizeType) 1;
          switch (virtual_pixel_method)
          {
            case BackgroundVirtualPixelMethod:
            case ConstantVirtualPixelMethod:
            case BlackVirtualPixelMethod:
            case GrayVirtualPixelMethod:
            case TransparentVirtualPixelMethod:
            case MaskVirtualPixelMethod:
            case WhiteVirtualPixelMethod:
            {
              p=(&virtual_pixel);
              virtual_indexes=(&virtual_index);
              break;
            }
            case EdgeVirtualPixelMethod:
            default:
            {
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                EdgeX(x_offset,cache_info->columns),
                EdgeY(y_offset,cache_info->rows),1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case RandomVirtualPixelMethod:
            {
              if (cache_info->random_info == (RandomInfo *) NULL)
                cache_info->random_info=AcquireRandomInfo();
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                RandomX(cache_info->random_info,cache_info->columns),
                RandomY(cache_info->random_info,cache_info->rows),1UL,1UL,
                *virtual_nexus,exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case DitherVirtualPixelMethod:
            {
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                DitherX(x_offset,cache_info->columns),
                DitherY(y_offset,cache_info->rows),1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case TileVirtualPixelMethod:
            {
              x_modulo=VirtualPixelModulo(x_offset,cache_info->columns);
              y_modulo=VirtualPixelModulo(y_offset,cache_info->rows);
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                x_modulo.remainder,y_modulo.remainder,1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case MirrorVirtualPixelMethod:
            {
              x_modulo=VirtualPixelModulo(x_offset,cache_info->columns);
              if ((x_modulo.quotient & 0x01) == 1L)
                x_modulo.remainder=(ssize_t) cache_info->columns-
                  x_modulo.remainder-1L;
              y_modulo=VirtualPixelModulo(y_offset,cache_info->rows);
              if ((y_modulo.quotient & 0x01) == 1L)
                y_modulo.remainder=(ssize_t) cache_info->rows-
                  y_modulo.remainder-1L;
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                x_modulo.remainder,y_modulo.remainder,1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case CheckerTileVirtualPixelMethod:
            {
              x_modulo=VirtualPixelModulo(x_offset,cache_info->columns);
              y_modulo=VirtualPixelModulo(y_offset,cache_info->rows);
              if (((x_modulo.quotient ^ y_modulo.quotient) & 0x01) != 0L)
                {
                  p=(&virtual_pixel);
                  virtual_indexes=(&virtual_index);
                  break;
                }
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                x_modulo.remainder,y_modulo.remainder,1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case HorizontalTileVirtualPixelMethod:
            {
              if ((y_offset < 0) || (y_offset >= (ssize_t) cache_info->rows))
                {
                  p=(&virtual_pixel);
                  virtual_indexes=(&virtual_index);
                  break;
                }
              x_modulo=VirtualPixelModulo(x_offset,cache_info->columns);
              y_modulo=VirtualPixelModulo(y_offset,cache_info->rows);
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                x_modulo.remainder,y_modulo.remainder,1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case VerticalTileVirtualPixelMethod:
            {
              if ((x_offset < 0) || (x_offset >= (ssize_t) cache_info->columns))
                {
                  p=(&virtual_pixel);
                  virtual_indexes=(&virtual_index);
                  break;
                }
              x_modulo=VirtualPixelModulo(x_offset,cache_info->columns);
              y_modulo=VirtualPixelModulo(y_offset,cache_info->rows);
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                x_modulo.remainder,y_modulo.remainder,1UL,1UL,*virtual_nexus,
                exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case HorizontalTileEdgeVirtualPixelMethod:
            {
              x_modulo=VirtualPixelModulo(x_offset,cache_info->columns);
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                x_modulo.remainder,EdgeY(y_offset,cache_info->rows),1UL,1UL,
                *virtual_nexus,exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
            case VerticalTileEdgeVirtualPixelMethod:
            {
              y_modulo=VirtualPixelModulo(y_offset,cache_info->rows);
              p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,
                EdgeX(x_offset,cache_info->columns),y_modulo.remainder,1UL,1UL,
                *virtual_nexus,exception);
              virtual_indexes=GetVirtualIndexesFromNexus(cache_info,
                *virtual_nexus);
              break;
            }
          }
          if (p == (const PixelPacket *) NULL)
            break;
          *q++=(*p);
          if ((indexes != (IndexPacket *) NULL) &&
              (virtual_indexes != (const IndexPacket *) NULL))
            *indexes++=(*virtual_indexes);
          continue;
        }
      /*
        Transfer a run of pixels.
      */
      p=GetVirtualPixelsFromNexus(image,virtual_pixel_method,x_offset,y_offset,
        (size_t) length,1UL,*virtual_nexus,exception);
      if (p == (const PixelPacket *) NULL)
        break;
      virtual_indexes=GetVirtualIndexesFromNexus(cache_info,*virtual_nexus);
      (void) memcpy(q,p,(size_t) length*sizeof(*p));
      q+=length;
      if ((indexes != (IndexPacket *) NULL) &&
          (virtual_indexes != (const IndexPacket *) NULL))
        {
          (void) memcpy(indexes,virtual_indexes,(size_t) length*
            sizeof(*virtual_indexes));
          indexes+=length;
        }
    }
  }
  virtual_nexus=DestroyPixelCacheNexus(virtual_nexus,1);
  return(pixels);
}
