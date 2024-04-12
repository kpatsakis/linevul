bool GLES2Util::ComputeImageDataSizesES3(
    int width, int height, int depth, int format, int type,
    const PixelStoreParams& params,
    uint32_t* size, uint32_t* opt_unpadded_row_size,
    uint32_t* opt_padded_row_size, uint32_t* opt_skip_size,
    uint32_t* opt_padding) {
  DCHECK(width >= 0 && height >= 0 && depth >= 0);

  uint32_t bytes_per_group = ComputeImageGroupSize(format, type);

  uint32_t unpadded_row_size;
  uint32_t padded_row_size;
  if (!ComputeImageRowSizeHelper(width, bytes_per_group, params.alignment,
                                 &unpadded_row_size, &padded_row_size,
                                 opt_padding)) {
    return false;
  }
  if (params.row_length > 0 &&
      !ComputeImageRowSizeHelper(params.row_length, bytes_per_group,
                                 params.alignment, nullptr, &padded_row_size,
                                 opt_padding)) {
    return false;
  }

  int image_height = params.image_height > 0 ? params.image_height : height;
  uint32_t num_of_rows;
  if (depth > 0) {
    if (!SafeMultiplyUint32(image_height, depth - 1, &num_of_rows) ||
        !SafeAddUint32(num_of_rows, height, &num_of_rows)) {
      return false;
    }
  } else {
    num_of_rows = 0;
  }

  if (num_of_rows > 0) {
    uint32_t size_of_all_but_last_row;
    if (!SafeMultiplyUint32((num_of_rows - 1), padded_row_size,
                            &size_of_all_but_last_row)) {
      return false;
    }
    if (!SafeAddUint32(size_of_all_but_last_row, unpadded_row_size, size)) {
      return false;
    }
  } else {
    *size = 0;
  }

  uint32_t skip_size = 0;
  if (params.skip_images > 0) {
    uint32_t image_size;
    if (!SafeMultiplyUint32(image_height, padded_row_size, &image_size))
      return false;
    if (!SafeMultiplyUint32(image_size, params.skip_images, &skip_size))
      return false;
  }
  if (params.skip_rows > 0) {
    uint32_t temp;
    if (!SafeMultiplyUint32(padded_row_size, params.skip_rows, &temp))
      return false;
    if (!SafeAddUint32(skip_size, temp, &skip_size))
      return false;
  }
  if (params.skip_pixels > 0) {
    uint32_t temp;
    if (!SafeMultiplyUint32(bytes_per_group, params.skip_pixels, &temp))
      return false;
    if (!SafeAddUint32(skip_size, temp, &skip_size))
      return false;
  }
  uint32_t total_size;
  if (!SafeAddUint32(*size, skip_size, &total_size))
    return false;

  if (opt_padded_row_size) {
    *opt_padded_row_size = padded_row_size;
  }
  if (opt_unpadded_row_size) {
    *opt_unpadded_row_size = unpadded_row_size;
  }
  if (opt_skip_size)
    *opt_skip_size = skip_size;
  return true;
}
