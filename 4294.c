void BaseRenderingContext2D::drawImage(
    ScriptState* script_state,
    const CanvasImageSourceUnion& image_source,
    double x,
    double y,
    ExceptionState& exception_state) {
  CanvasImageSource* image_source_internal =
      ToImageSourceInternal(image_source, exception_state);
  if (!image_source_internal)
    return;
  FloatSize default_object_size(Width(), Height());
  FloatSize source_rect_size =
      image_source_internal->ElementSize(default_object_size);
  FloatSize dest_rect_size =
      image_source_internal->DefaultDestinationSize(default_object_size);
  drawImage(script_state, image_source_internal, 0, 0, source_rect_size.Width(),
            source_rect_size.Height(), x, y, dest_rect_size.Width(),
            dest_rect_size.Height(), exception_state);
}
