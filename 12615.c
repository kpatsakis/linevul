void BaseRenderingContext2D::putImageData(ImageData* data,
                                          int dx,
                                          int dy,
                                          int dirty_x,
                                          int dirty_y,
                                          int dirty_width,
                                          int dirty_height,
                                          ExceptionState& exception_state) {
  if (!WTF::CheckMul(dirty_width, dirty_height).IsValid<int>()) {
    return;
  }
  usage_counters_.num_put_image_data_calls++;
  usage_counters_.area_put_image_data_calls += dirty_width * dirty_height;

  if (data->BufferBase()->IsNeutered()) {
    exception_state.ThrowDOMException(kInvalidStateError,
                                      "The source data has been neutered.");
    return;
  }

  ImageBuffer* buffer = GetImageBuffer();
  if (!buffer)
    return;

  if (dirty_width < 0) {
    dirty_x += dirty_width;
    dirty_width = -dirty_width;
  }

  if (dirty_height < 0) {
    dirty_y += dirty_height;
    dirty_height = -dirty_height;
  }

  IntRect dest_rect(dirty_x, dirty_y, dirty_width, dirty_height);
  dest_rect.Intersect(IntRect(0, 0, data->width(), data->height()));
  IntSize dest_offset(static_cast<int>(dx), static_cast<int>(dy));
  dest_rect.Move(dest_offset);
  dest_rect.Intersect(IntRect(IntPoint(), buffer->Size()));
  if (dest_rect.IsEmpty())
    return;

  Optional<ScopedUsHistogramTimer> timer;
  if (!IsPaint2D()) {
    if (GetImageBuffer() && GetImageBuffer()->IsAccelerated()) {
      DEFINE_THREAD_SAFE_STATIC_LOCAL(
          CustomCountHistogram, scoped_us_counter_gpu,
          ("Blink.Canvas.PutImageData.GPU", 0, 10000000, 50));
      timer.emplace(scoped_us_counter_gpu);
    } else {
      DEFINE_THREAD_SAFE_STATIC_LOCAL(
          CustomCountHistogram, scoped_us_counter_cpu,
          ("Blink.Canvas.PutImageData.CPU", 0, 10000000, 50));
      timer.emplace(scoped_us_counter_cpu);
    }
  }

  IntRect source_rect(dest_rect);
  source_rect.Move(-dest_offset);

  CheckOverdraw(dest_rect, nullptr, CanvasRenderingContext2DState::kNoImage,
                kUntransformedUnclippedFill);

  CanvasColorParams data_color_params = data->GetCanvasColorParams();
  CanvasColorParams context_color_params =
      CanvasColorParams(ColorSpace(), PixelFormat(), kNonOpaque);
  if (data_color_params.NeedsColorConversion(context_color_params) ||
      PixelFormat() == kF16CanvasPixelFormat) {
    unsigned data_length =
        data->Size().Area() * context_color_params.BytesPerPixel();
    std::unique_ptr<uint8_t[]> converted_pixels(new uint8_t[data_length]);
    if (data->ImageDataInCanvasColorSettings(ColorSpace(), PixelFormat(),
                                             converted_pixels.get(),
                                             kRGBAColorType)) {
      buffer->PutByteArray(converted_pixels.get(),
                           IntSize(data->width(), data->height()), source_rect,
                           IntPoint(dest_offset));
    }
  } else {
    buffer->PutByteArray(data->data()->Data(),
                         IntSize(data->width(), data->height()), source_rect,
                         IntPoint(dest_offset));
  }
  DidDraw(dest_rect);
}
