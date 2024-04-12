static Image *ReadEMFImage(const ImageInfo *image_info,
  ExceptionInfo *exception)
{
  Gdiplus::Bitmap
    *bitmap;

  Gdiplus::BitmapData
     bitmap_data;

  Gdiplus::GdiplusStartupInput
    startup_input;

  Gdiplus::Graphics
    *graphics;

  Gdiplus::Image
    *source;

  Gdiplus::Rect
    rect;

  GeometryInfo
    geometry_info;

  Image
    *image;

  MagickStatusType
    flags;

  register PixelPacket
    *q;

  register ssize_t
    x;

  ssize_t
    y;

  ULONG_PTR
    token;

  unsigned char
    *p;

  wchar_t
    fileName[MaxTextExtent];

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",
      image_info->filename);
  assert(exception != (ExceptionInfo *) NULL);

  image=AcquireImage(image_info);
  if (Gdiplus::GdiplusStartup(&token,&startup_input,NULL) != 
    Gdiplus::Status::Ok)
    ThrowReaderException(CoderError, "GdiplusStartupFailed");
  MultiByteToWideChar(CP_UTF8,0,image->filename,-1,fileName,MaxTextExtent);
  source=Gdiplus::Image::FromFile(fileName);
  if (source == (Gdiplus::Image *) NULL)
    {
      Gdiplus::GdiplusShutdown(token);
      ThrowReaderException(FileOpenError,"UnableToOpenFile");
    }

  image->x_resolution=source->GetHorizontalResolution();
  image->y_resolution=source->GetVerticalResolution();
  image->columns=(size_t) source->GetWidth();
  image->rows=(size_t) source->GetHeight();
  if (image_info->density != (char *) NULL)
    {
      flags=ParseGeometry(image_info->density,&geometry_info);
      image->x_resolution=geometry_info.rho;
      image->y_resolution=geometry_info.sigma;
      if ((flags & SigmaValue) == 0)
        image->y_resolution=image->x_resolution;
      if ((image->x_resolution > 0.0) && (image->y_resolution > 0.0))
        {
          image->columns=(size_t) floor((Gdiplus::REAL) source->GetWidth() /
            source->GetHorizontalResolution() * image->x_resolution + 0.5);
          image->rows=(size_t)floor((Gdiplus::REAL) source->GetHeight() /
            source->GetVerticalResolution() * image->y_resolution + 0.5);
        }
    }

  bitmap=new Gdiplus::Bitmap((INT) image->columns,(INT) image->rows,
    PixelFormat32bppARGB);
  graphics=Gdiplus::Graphics::FromImage(bitmap);
  graphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
  graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
  graphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
  graphics->Clear(Gdiplus::Color((BYTE) ScaleQuantumToChar(QuantumRange-
    image->background_color.opacity),(BYTE) ScaleQuantumToChar(
    image->background_color.red),(BYTE) ScaleQuantumToChar(
    image->background_color.green),(BYTE) ScaleQuantumToChar(
    image->background_color.blue)));
  graphics->DrawImage(source,0,0,(INT) image->columns,(INT) image->rows);
  delete graphics;
  delete source;

  rect=Gdiplus::Rect(0,0,(INT) image->columns,(INT) image->rows);
  if (bitmap->LockBits(&rect,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,
    &bitmap_data) != Gdiplus::Ok)
  {
    delete bitmap;
    Gdiplus::GdiplusShutdown(token);
    ThrowReaderException(FileOpenError,"UnableToReadImageData");
  }

  image->matte=MagickTrue;
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    p=(unsigned char *) bitmap_data.Scan0+(y*abs(bitmap_data.Stride));
    if (bitmap_data.Stride < 0)
      q=GetAuthenticPixels(image,0,image->rows-y-1,image->columns,1,exception);
    else
      q=GetAuthenticPixels(image,0,y,image->columns,1,exception);
    if (q == (PixelPacket *) NULL)
      break;

    for (x=0; x < (ssize_t) image->columns; x++)
    {
      SetPixelBlue(q,ScaleCharToQuantum(*p++));
      SetPixelGreen(q,ScaleCharToQuantum(*p++));
      SetPixelRed(q,ScaleCharToQuantum(*p++));
      SetPixelAlpha(q,ScaleCharToQuantum(*p++));
      q++;
    }

    if (SyncAuthenticPixels(image,exception) == MagickFalse)
      break;
  }

  bitmap->UnlockBits(&bitmap_data);
  delete bitmap;
  Gdiplus::GdiplusShutdown(token);
  return(image);
}