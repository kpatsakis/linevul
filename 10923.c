std::string EncodeImage(const gfx::Image& image,
                        const std::string& format,
                        int quality) {
  DCHECK(!image.IsEmpty());

  scoped_refptr<base::RefCountedMemory> data;
  if (format == kPng) {
    data = image.As1xPNGBytes();
  } else if (format == kJpeg) {
    scoped_refptr<base::RefCountedBytes> bytes(new base::RefCountedBytes());
    if (gfx::JPEG1xEncodedDataFromImage(image, quality, &bytes->data()))
      data = bytes;
  }

  if (!data || !data->front())
    return std::string();

  std::string base_64_data;
  base::Base64Encode(
      base::StringPiece(reinterpret_cast<const char*>(data->front()),
                        data->size()),
      &base_64_data);

  return base_64_data;
}
