void BaseRenderingContext2D::fillRect(double x,
                                      double y,
                                      double width,
                                      double height) {
  if (!ValidateRectForCanvas(x, y, width, height))
    return;

  if (!DrawingCanvas())
    return;

  SkRect rect = SkRect::MakeXYWH(x, y, width, height);
  Draw([&rect](PaintCanvas* c, const PaintFlags* flags)  // draw lambda
       { c->drawRect(rect, *flags); },
       [&rect, this](const SkIRect& clip_bounds)  // overdraw test lambda
       { return RectContainsTransformedRect(rect, clip_bounds); },
       rect, CanvasRenderingContext2DState::kFillPaintType);
}
