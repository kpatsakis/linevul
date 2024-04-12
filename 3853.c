void BaseRenderingContext2D::fillStyle(
    StringOrCanvasGradientOrCanvasPattern& return_value) const {
  ConvertCanvasStyleToUnionType(GetState().FillStyle(), return_value);
}
