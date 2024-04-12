static Image *ReadWPGImage(const ImageInfo *image_info,
  ExceptionInfo *exception)
{
  typedef struct
  {
    size_t FileId;
    MagickOffsetType DataOffset;
    unsigned int ProductType;
    unsigned int FileType;
    unsigned char MajorVersion;
    unsigned char MinorVersion;
    unsigned int EncryptKey;
    unsigned int Reserved;
  } WPGHeader;

  typedef struct
  {
    unsigned char RecType;
    size_t RecordLength;
  } WPGRecord;

  typedef struct
  {
    unsigned char Class;
    unsigned char RecType;
    size_t Extension;
    size_t RecordLength;
  } WPG2Record;

  typedef struct
  {
    unsigned  HorizontalUnits;
    unsigned  VerticalUnits;
    unsigned char PosSizePrecision;
  } WPG2Start;

  typedef struct
  {
    unsigned int Width;
    unsigned int Height;
    unsigned int Depth;
    unsigned int HorzRes;
    unsigned int VertRes;
  } WPGBitmapType1;

  typedef struct
  {
    unsigned int Width;
    unsigned int Height;
    unsigned char Depth;
    unsigned char Compression;
  } WPG2BitmapType1;

  typedef struct
  {
    unsigned int RotAngle;
    unsigned int LowLeftX;
    unsigned int LowLeftY;
    unsigned int UpRightX;
    unsigned int UpRightY;
    unsigned int Width;
    unsigned int Height;
    unsigned int Depth;
    unsigned int HorzRes;
    unsigned int VertRes;
  } WPGBitmapType2;

  typedef struct
  {
    unsigned int StartIndex;
    unsigned int NumOfEntries;
  } WPGColorMapRec;

  /*
  typedef struct {
    size_t PS_unknown1;
    unsigned int PS_unknown2;
    unsigned int PS_unknown3;
  } WPGPSl1Record;  
  */

  Image
    *image;

  unsigned int
    status;

  WPGHeader
    Header;

  WPGRecord
    Rec;

  WPG2Record
    Rec2;

  WPG2Start StartWPG;

  WPGBitmapType1
    BitmapHeader1;

  WPG2BitmapType1
    Bitmap2Header1;

  WPGBitmapType2
    BitmapHeader2;

  WPGColorMapRec
    WPG_Palette;

  int
    i,
    bpp,
    WPG2Flags;

  ssize_t
    ldblk;

  size_t
    one;

  unsigned char
    *BImgBuff;

  tCTM CTM;         /*current transform matrix*/

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  one=1;
  image=AcquireImage(image_info,exception);
  image->depth=8;
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFalse)
    {
      image=DestroyImageList(image);
      return((Image *) NULL);
    }
  /*
    Read WPG image.
  */
  Header.FileId=ReadBlobLSBLong(image);
  Header.DataOffset=(MagickOffsetType) ReadBlobLSBLong(image);
  Header.ProductType=ReadBlobLSBShort(image);
  Header.FileType=ReadBlobLSBShort(image);
  Header.MajorVersion=ReadBlobByte(image);
  Header.MinorVersion=ReadBlobByte(image);
  Header.EncryptKey=ReadBlobLSBShort(image);
  Header.Reserved=ReadBlobLSBShort(image);

  if (Header.FileId!=0x435057FF || (Header.ProductType>>8)!=0x16)
    ThrowReaderException(CorruptImageError,"ImproperImageHeader");
  if (Header.EncryptKey!=0)
    ThrowReaderException(CoderError,"EncryptedWPGImageFileNotSupported");

  image->columns = 1;
  image->rows = 1;
  image->colors = 0;
  bpp=0;
  BitmapHeader2.RotAngle=0;

  switch(Header.FileType)
    {
    case 1:     /* WPG level 1 */
      while(!EOFBlob(image)) /* object parser loop */
        {
          (void) SeekBlob(image,Header.DataOffset,SEEK_SET);
          if(EOFBlob(image))
            break;

          Rec.RecType=(i=ReadBlobByte(image));
          if(i==EOF)
            break;
          Rd_WP_DWORD(image,&Rec.RecordLength);
          if(EOFBlob(image))
            break;

          Header.DataOffset=TellBlob(image)+Rec.RecordLength;

          switch(Rec.RecType)
            {
            case 0x0B: /* bitmap type 1 */
              BitmapHeader1.Width=ReadBlobLSBShort(image);
              BitmapHeader1.Height=ReadBlobLSBShort(image);
              if ((BitmapHeader1.Width == 0) || (BitmapHeader1.Height == 0))
                ThrowReaderException(CorruptImageError,"ImproperImageHeader");
              BitmapHeader1.Depth=ReadBlobLSBShort(image);
              BitmapHeader1.HorzRes=ReadBlobLSBShort(image);
              BitmapHeader1.VertRes=ReadBlobLSBShort(image);

              if(BitmapHeader1.HorzRes && BitmapHeader1.VertRes)
                {
                  image->units=PixelsPerCentimeterResolution;
                  image->resolution.x=BitmapHeader1.HorzRes/470.0;
                  image->resolution.y=BitmapHeader1.VertRes/470.0;
                }
              image->columns=BitmapHeader1.Width;
              image->rows=BitmapHeader1.Height;
              bpp=BitmapHeader1.Depth;

              goto UnpackRaster;

            case 0x0E:  /*Color palette */
              WPG_Palette.StartIndex=ReadBlobLSBShort(image);
              WPG_Palette.NumOfEntries=ReadBlobLSBShort(image);

              image->colors=WPG_Palette.NumOfEntries;
              if (!AcquireImageColormap(image,image->colors,exception))
                goto NoMemory;
              for (i=WPG_Palette.StartIndex;
                   i < (int)WPG_Palette.NumOfEntries; i++)
                {
                  image->colormap[i].red=ScaleCharToQuantum((unsigned char)
                    ReadBlobByte(image));
                  image->colormap[i].green=ScaleCharToQuantum((unsigned char)
                    ReadBlobByte(image));
                  image->colormap[i].blue=ScaleCharToQuantum((unsigned char)
                    ReadBlobByte(image));
                }
              break;
     
            case 0x11:  /* Start PS l1 */
              if(Rec.RecordLength > 8)
                image=ExtractPostscript(image,image_info,
                  TellBlob(image)+8,   /* skip PS header in the wpg */
                  (ssize_t) Rec.RecordLength-8,exception);
              break;     

            case 0x14:  /* bitmap type 2 */
              BitmapHeader2.RotAngle=ReadBlobLSBShort(image);
              BitmapHeader2.LowLeftX=ReadBlobLSBShort(image);
              BitmapHeader2.LowLeftY=ReadBlobLSBShort(image);
              BitmapHeader2.UpRightX=ReadBlobLSBShort(image);
              BitmapHeader2.UpRightY=ReadBlobLSBShort(image);
              BitmapHeader2.Width=ReadBlobLSBShort(image);
              BitmapHeader2.Height=ReadBlobLSBShort(image);
              if ((BitmapHeader2.Width == 0) || (BitmapHeader2.Height == 0))
                ThrowReaderException(CorruptImageError,"ImproperImageHeader");
              BitmapHeader2.Depth=ReadBlobLSBShort(image);
              BitmapHeader2.HorzRes=ReadBlobLSBShort(image);
              BitmapHeader2.VertRes=ReadBlobLSBShort(image);

              image->units=PixelsPerCentimeterResolution;
              image->page.width=(unsigned int)
                ((BitmapHeader2.LowLeftX-BitmapHeader2.UpRightX)/470.0);
              image->page.height=(unsigned int)
                ((BitmapHeader2.LowLeftX-BitmapHeader2.UpRightY)/470.0);
              image->page.x=(int) (BitmapHeader2.LowLeftX/470.0);
              image->page.y=(int) (BitmapHeader2.LowLeftX/470.0);
              if(BitmapHeader2.HorzRes && BitmapHeader2.VertRes)
                {
                  image->resolution.x=BitmapHeader2.HorzRes/470.0;
                  image->resolution.y=BitmapHeader2.VertRes/470.0;
                }
              image->columns=BitmapHeader2.Width;
              image->rows=BitmapHeader2.Height;
              bpp=BitmapHeader2.Depth;

            UnpackRaster:      
              status=SetImageExtent(image,image->columns,image->rows,exception);
              if (status == MagickFalse)
                break;
              if ((image->colors == 0) && (bpp != 24))
                {
                  image->colors=one << bpp;
                  if (!AcquireImageColormap(image,image->colors,exception))
                    {
                    NoMemory:
                      ThrowReaderException(ResourceLimitError,
                        "MemoryAllocationFailed");
                    }
                  /* printf("Load default colormap \n"); */
                  for (i=0; (i < (int) image->colors) && (i < 256); i++)
                    {               
                      image->colormap[i].red=ScaleCharToQuantum(WPG1_Palette[i].Red);
                      image->colormap[i].green=ScaleCharToQuantum(WPG1_Palette[i].Green);
                      image->colormap[i].blue=ScaleCharToQuantum(WPG1_Palette[i].Blue);
                    }
                }
              else
                {
                  if (bpp < 24)
                    if ( (image->colors < (one << bpp)) && (bpp != 24) )
                      image->colormap=(PixelInfo *) ResizeQuantumMemory(
                        image->colormap,(size_t) (one << bpp),
                        sizeof(*image->colormap));
                }
          
              if (bpp == 1)
                {
                  if(image->colormap[0].red==0 &&
                     image->colormap[0].green==0 &&
                     image->colormap[0].blue==0 &&
                     image->colormap[1].red==0 &&
                     image->colormap[1].green==0 &&
                     image->colormap[1].blue==0)
                    {  /* fix crippled monochrome palette */
                      image->colormap[1].red =
                        image->colormap[1].green =
                        image->colormap[1].blue = QuantumRange;
                    }
                }      

              if(UnpackWPGRaster(image,bpp,exception) < 0)
                /* The raster cannot be unpacked */
                {
                DecompressionFailed:
                  ThrowReaderException(CoderError,"UnableToDecompressImage");
                    }

              if(Rec.RecType==0x14 && BitmapHeader2.RotAngle!=0 && !image_info->ping)
                {  
                  /* flop command */
                  if(BitmapHeader2.RotAngle & 0x8000)
                    {
                      Image
                        *flop_image;

                      flop_image = FlopImage(image, exception);
                      if (flop_image != (Image *) NULL) {
                        DuplicateBlob(flop_image,image);
                        (void) RemoveLastImageFromList(&image);
                        AppendImageToList(&image,flop_image);
                      }
                    }
                  /* flip command */
                  if(BitmapHeader2.RotAngle & 0x2000)
                    {
                      Image
                        *flip_image;

                      flip_image = FlipImage(image, exception);
                      if (flip_image != (Image *) NULL) {
                        DuplicateBlob(flip_image,image);
                        (void) RemoveLastImageFromList(&image);
                        AppendImageToList(&image,flip_image);
                      }
                    }
                  /* rotate command */
                  if(BitmapHeader2.RotAngle & 0x0FFF)
                    {
                      Image
                        *rotate_image;

                      rotate_image=RotateImage(image,(BitmapHeader2.RotAngle &
                        0x0FFF), exception);
                      if (rotate_image != (Image *) NULL) {
                        DuplicateBlob(rotate_image,image);
                        (void) RemoveLastImageFromList(&image);
                        AppendImageToList(&image,rotate_image);
                      }
                    }
                }

              /* Allocate next image structure. */
              AcquireNextImage(image_info,image,exception);
              image->depth=8;
              if (image->next == (Image *) NULL)
                goto Finish;
              image=SyncNextImageInList(image);
              image->columns=image->rows=1;
              image->colors=0;
              break;

            case 0x1B:  /* Postscript l2 */
              if(Rec.RecordLength>0x3C)
                image=ExtractPostscript(image,image_info,
                  TellBlob(image)+0x3C,   /* skip PS l2 header in the wpg */
                  (ssize_t) Rec.RecordLength-0x3C,exception);
              break;
            }
        }
      break;

    case 2:  /* WPG level 2 */
      (void) memset(CTM,0,sizeof(CTM));
      StartWPG.PosSizePrecision = 0;
      while(!EOFBlob(image)) /* object parser loop */
        {
          (void) SeekBlob(image,Header.DataOffset,SEEK_SET);
          if(EOFBlob(image))
            break;

          Rec2.Class=(i=ReadBlobByte(image));
          if(i==EOF)
            break;
          Rec2.RecType=(i=ReadBlobByte(image));
          if(i==EOF)
            break;
          Rd_WP_DWORD(image,&Rec2.Extension);
          Rd_WP_DWORD(image,&Rec2.RecordLength);
          if(EOFBlob(image))
            break;

          Header.DataOffset=TellBlob(image)+Rec2.RecordLength;

          switch(Rec2.RecType)
            {
      case 1:
              StartWPG.HorizontalUnits=ReadBlobLSBShort(image);
              StartWPG.VerticalUnits=ReadBlobLSBShort(image);
              StartWPG.PosSizePrecision=ReadBlobByte(image);
              break;
            case 0x0C:    /* Color palette */
              WPG_Palette.StartIndex=ReadBlobLSBShort(image);
              WPG_Palette.NumOfEntries=ReadBlobLSBShort(image);

              image->colors=WPG_Palette.NumOfEntries;
              if (AcquireImageColormap(image,image->colors,exception) == MagickFalse)
                ThrowReaderException(ResourceLimitError,
                  "MemoryAllocationFailed");
              for (i=WPG_Palette.StartIndex;
                   i < (int)WPG_Palette.NumOfEntries; i++)
                {
                  image->colormap[i].red=ScaleCharToQuantum((char)
                    ReadBlobByte(image));
                  image->colormap[i].green=ScaleCharToQuantum((char)
                    ReadBlobByte(image));
                  image->colormap[i].blue=ScaleCharToQuantum((char)
                    ReadBlobByte(image));
                  (void) ReadBlobByte(image);   /*Opacity??*/
                }
              break;
            case 0x0E:
              Bitmap2Header1.Width=ReadBlobLSBShort(image);
              Bitmap2Header1.Height=ReadBlobLSBShort(image);
              if ((Bitmap2Header1.Width == 0) || (Bitmap2Header1.Height == 0))
                ThrowReaderException(CorruptImageError,"ImproperImageHeader");
              Bitmap2Header1.Depth=ReadBlobByte(image);
              Bitmap2Header1.Compression=ReadBlobByte(image);

              if(Bitmap2Header1.Compression > 1)
                continue; /*Unknown compression method */
              switch(Bitmap2Header1.Depth)
                {
                case 1:
                  bpp=1;
                  break;
                case 2:
                  bpp=2;
                  break;
                case 3:
                  bpp=4;
                  break;
                case 4:
                  bpp=8;
                  break;
                case 8:
                  bpp=24;
                  break;
                default:
                  continue;  /*Ignore raster with unknown depth*/
                }
              image->columns=Bitmap2Header1.Width;
              image->rows=Bitmap2Header1.Height;
               status=SetImageExtent(image,image->columns,image->rows,exception);
               if (status == MagickFalse)
                 break;
               if ((image->colors == 0) && (bpp != 24))
                 {
                   size_t
                    one;

                  one=1;
                  image->colors=one << bpp;
                  if (!AcquireImageColormap(image,image->colors,exception))
                    goto NoMemory;
                }
              else
                {
                  if(bpp < 24)
                    if( image->colors<(one << bpp) && bpp!=24 )
                      image->colormap=(PixelInfo *) ResizeQuantumMemory(
                       image->colormap,(size_t) (one << bpp),
                       sizeof(*image->colormap));
                }


              switch(Bitmap2Header1.Compression)
                {
                case 0:    /*Uncompressed raster*/
                  {
                    ldblk=(ssize_t) ((bpp*image->columns+7)/8);
                    BImgBuff=(unsigned char *) AcquireQuantumMemory((size_t)
                      ldblk+1,sizeof(*BImgBuff));
                    if (BImgBuff == (unsigned char *) NULL)
                      goto NoMemory;

                    for(i=0; i< (ssize_t) image->rows; i++)
                      {
                        (void) ReadBlob(image,ldblk,BImgBuff);
                        InsertRow(image,BImgBuff,i,bpp,exception);
                      }

                    if(BImgBuff)
                      BImgBuff=(unsigned char *) RelinquishMagickMemory(BImgBuff);
                    break;
                  }
                case 1:    /*RLE for WPG2 */
                  {
                    if( UnpackWPG2Raster(image,bpp,exception) < 0)
                      goto DecompressionFailed;
                    break;
                  }   
                }

              if(CTM[0][0]<0 && !image_info->ping)
                {    /*?? RotAngle=360-RotAngle;*/
                  Image
                    *flop_image;

                  flop_image = FlopImage(image, exception);
                  if (flop_image != (Image *) NULL) {
                    DuplicateBlob(flop_image,image);
                    (void) RemoveLastImageFromList(&image);
                    AppendImageToList(&image,flop_image);
                  }
                  /* Try to change CTM according to Flip - I am not sure, must be checked.
                     Tx(0,0)=-1;      Tx(1,0)=0;   Tx(2,0)=0;
                     Tx(0,1)= 0;      Tx(1,1)=1;   Tx(2,1)=0;
                     Tx(0,2)=(WPG._2Rect.X_ur+WPG._2Rect.X_ll);
                     Tx(1,2)=0;   Tx(2,2)=1; */
                }
              if(CTM[1][1]<0 && !image_info->ping)
                {    /*?? RotAngle=360-RotAngle;*/
                  Image
                    *flip_image;

                   flip_image = FlipImage(image, exception);
                   if (flip_image != (Image *) NULL) {
                     DuplicateBlob(flip_image,image);
                     (void) RemoveLastImageFromList(&image);
                     AppendImageToList(&image,flip_image);
                    }
                  /* Try to change CTM according to Flip - I am not sure, must be checked.
                     float_matrix Tx(3,3);
                     Tx(0,0)= 1;   Tx(1,0)= 0;   Tx(2,0)=0;
                     Tx(0,1)= 0;   Tx(1,1)=-1;   Tx(2,1)=0;
                     Tx(0,2)= 0;   Tx(1,2)=(WPG._2Rect.Y_ur+WPG._2Rect.Y_ll);
                     Tx(2,2)=1; */
              }


              /* Allocate next image structure. */
              AcquireNextImage(image_info,image,exception);
              image->depth=8;
              if (image->next == (Image *) NULL)
                goto Finish;
              image=SyncNextImageInList(image);
              image->columns=image->rows=1;
              image->colors=0;
              break;

            case 0x12:  /* Postscript WPG2*/
        i=ReadBlobLSBShort(image);
              if(Rec2.RecordLength > (unsigned int) i)
                image=ExtractPostscript(image,image_info,
                  TellBlob(image)+i,    /*skip PS header in the wpg2*/
                  (ssize_t) (Rec2.RecordLength-i-2),exception);
              break;

      case 0x1B:          /*bitmap rectangle*/
              WPG2Flags = LoadWPG2Flags(image,StartWPG.PosSizePrecision,NULL,&CTM);
              (void) WPG2Flags;
              break;
            }
        }

      break;

    default:
      {
         ThrowReaderException(CoderError,"DataEncodingSchemeIsNotSupported");
      }
   }

 Finish:
  (void) CloseBlob(image);

  {
    Image
      *p;

    ssize_t
      scene=0;

    /*
      Rewind list, removing any empty images while rewinding.
    */
    p=image;
    image=NULL;
    while (p != (Image *) NULL)
      {
        Image *tmp=p;
        if ((p->rows == 0) || (p->columns == 0)) {
          p=p->previous;
          DeleteImageFromList(&tmp);
        } else {
          image=p;
          p=p->previous;
        }
      }
    /*
      Fix scene numbers.
    */
    for (p=image; p != (Image *) NULL; p=p->next)
      p->scene=(size_t) scene++;
  }
  if (image == (Image *) NULL)
    ThrowReaderException(CorruptImageError,
      "ImageFileDoesNotContainAnyImageData");
  return(image);
}