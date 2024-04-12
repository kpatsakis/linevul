static inline size_t WriteChannelSize(const PSDInfo *psd_info,Image *image,
  const signed short channel)
{
  size_t
    count;

  count=WriteBlobMSBSignedShort(image,channel);
  count+=SetPSDSize(psd_info,image,0);
  return(count);
}
