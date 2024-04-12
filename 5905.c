 scoped_refptr<VASurface> VaapiJpegDecoder::Decode(
     base::span<const uint8_t> encoded_image,
     VaapiImageDecodeStatus* status) {
  if (!vaapi_wrapper_) {
    VLOGF(1) << "VaapiJpegDecoder has not been initialized";
    *status = VaapiImageDecodeStatus::kInvalidState;
    return nullptr;
  }

  JpegParseResult parse_result;
  if (!ParseJpegPicture(encoded_image.data(), encoded_image.size(),
                        &parse_result)) {
    VLOGF(1) << "ParseJpegPicture failed";
    *status = VaapiImageDecodeStatus::kParseJpegFailed;
    return nullptr;
  }

  const unsigned int picture_va_rt_format =
      VaSurfaceFormatForJpeg(parse_result.frame_header);
  if (picture_va_rt_format == kInvalidVaRtFormat) {
    VLOGF(1) << "Unsupported subsampling";
    *status = VaapiImageDecodeStatus::kUnsupportedSubsampling;
    return nullptr;
  }

  if (!IsVaapiSupportedJpeg(parse_result)) {
    VLOGF(1) << "The supplied JPEG is unsupported";
    *status = VaapiImageDecodeStatus::kUnsupportedJpeg;
    return nullptr;
  }

  const gfx::Size new_coded_size(
      base::strict_cast<int>(parse_result.frame_header.coded_width),
      base::strict_cast<int>(parse_result.frame_header.coded_height));
  if (new_coded_size != coded_size_ || va_surface_id_ == VA_INVALID_SURFACE ||
      picture_va_rt_format != va_rt_format_) {
    vaapi_wrapper_->DestroyContextAndSurfaces(
        std::vector<VASurfaceID>({va_surface_id_}));
    va_surface_id_ = VA_INVALID_SURFACE;
    va_rt_format_ = picture_va_rt_format;

    std::vector<VASurfaceID> va_surfaces;
    if (!vaapi_wrapper_->CreateContextAndSurfaces(va_rt_format_, new_coded_size,
                                                  1, &va_surfaces)) {
      VLOGF(1) << "Could not create the context or the surface";
      *status = VaapiImageDecodeStatus::kSurfaceCreationFailed;
      return nullptr;
    }
    va_surface_id_ = va_surfaces[0];
    coded_size_ = new_coded_size;
  }

  VAPictureParameterBufferJPEGBaseline pic_param{};
  FillPictureParameters(parse_result.frame_header, &pic_param);
  if (!vaapi_wrapper_->SubmitBuffer(VAPictureParameterBufferType, &pic_param)) {
    VLOGF(1) << "Could not submit VAPictureParameterBufferType";
    *status = VaapiImageDecodeStatus::kSubmitPicParamsFailed;
    return nullptr;
  }

  VAIQMatrixBufferJPEGBaseline iq_matrix{};
  FillIQMatrix(parse_result.q_table, &iq_matrix);
  if (!vaapi_wrapper_->SubmitBuffer(VAIQMatrixBufferType, &iq_matrix)) {
    VLOGF(1) << "Could not submit VAIQMatrixBufferType";
    *status = VaapiImageDecodeStatus::kSubmitIQMatrixFailed;
    return nullptr;
  }

  VAHuffmanTableBufferJPEGBaseline huffman_table{};
  FillHuffmanTable(parse_result.dc_table, parse_result.ac_table,
                   &huffman_table);
  if (!vaapi_wrapper_->SubmitBuffer(VAHuffmanTableBufferType, &huffman_table)) {
    VLOGF(1) << "Could not submit VAHuffmanTableBufferType";
    *status = VaapiImageDecodeStatus::kSubmitHuffmanFailed;
    return nullptr;
  }

  VASliceParameterBufferJPEGBaseline slice_param{};
  FillSliceParameters(parse_result, &slice_param);
  if (!vaapi_wrapper_->SubmitBuffer(VASliceParameterBufferType, &slice_param)) {
    VLOGF(1) << "Could not submit VASliceParameterBufferType";
    *status = VaapiImageDecodeStatus::kSubmitSliceParamsFailed;
    return nullptr;
  }

  if (!vaapi_wrapper_->SubmitBuffer(VASliceDataBufferType,
                                    parse_result.data_size,
                                    const_cast<char*>(parse_result.data))) {
    VLOGF(1) << "Could not submit VASliceDataBufferType";
    *status = VaapiImageDecodeStatus::kSubmitSliceDataFailed;
    return nullptr;
  }

  if (!vaapi_wrapper_->ExecuteAndDestroyPendingBuffers(va_surface_id_)) {
    VLOGF(1) << "Executing the decode failed";
    *status = VaapiImageDecodeStatus::kExecuteDecodeFailed;
    return nullptr;
  }

  *status = VaapiImageDecodeStatus::kSuccess;
  return base::MakeRefCounted<VASurface>(va_surface_id_, coded_size_,
                                         va_rt_format_,
                                          base::DoNothing() /* release_cb */);
 }
