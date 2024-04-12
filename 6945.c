void CaptureVisibleTabFunction::SendResultFromBitmap(
    const SkBitmap& screen_capture) {
  scoped_refptr<RefCountedBytes> image_data(new RefCountedBytes);
  SkAutoLockPixels screen_capture_lock(screen_capture);
  bool encoded = false;
  std::string mime_type;
  switch (image_format_) {
    case FORMAT_JPEG:
      encoded = gfx::JPEGCodec::Encode(
          reinterpret_cast<unsigned char*>(screen_capture.getAddr32(0, 0)),
          gfx::JPEGCodec::FORMAT_BGRA,
          screen_capture.width(),
          screen_capture.height(),
          static_cast<int>(screen_capture.rowBytes()), image_quality_,
          &image_data->data);
      mime_type = keys::kMimeTypeJpeg;
      break;
    case FORMAT_PNG:
      encoded = gfx::PNGCodec::Encode(
          reinterpret_cast<unsigned char*>(screen_capture.getAddr32(0, 0)),
          gfx::PNGCodec::FORMAT_BGRA,
          screen_capture.width(),
          screen_capture.height(),
          static_cast<int>(screen_capture.rowBytes()), false,
          &image_data->data);
      mime_type = keys::kMimeTypePng;
      break;
    default:
      NOTREACHED() << "Invalid image format.";
  }

  if (!encoded) {
    error_ = ExtensionErrorUtils::FormatErrorMessage(
        keys::kInternalVisibleTabCaptureError, "");
    SendResponse(false);
    return;
  }

  std::string base64_result;
  std::string stream_as_string;
  stream_as_string.resize(image_data->data.size());
  memcpy(&stream_as_string[0],
      reinterpret_cast<const char*>(&image_data->data[0]),
      image_data->data.size());

  base::Base64Encode(stream_as_string, &base64_result);
  base64_result.insert(0, StringPrintf("data:%s;base64,", mime_type.c_str()));
  result_.reset(new StringValue(base64_result));
  SendResponse(true);
}
