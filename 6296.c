ModuleExport size_t RegisterYUVImage(void)
{
  MagickInfo
    *entry;

  entry=AcquireMagickInfo("YUV","YUV","CCIR 601 4:1:1 or 4:2:2");
  entry->decoder=(DecodeImageHandler *) ReadYUVImage;
  entry->encoder=(EncodeImageHandler *) WriteYUVImage;
  entry->flags^=CoderAdjoinFlag;
  entry->flags|=CoderRawSupportFlag;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}
