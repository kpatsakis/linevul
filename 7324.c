String BaseRenderingContext2D::globalCompositeOperation() const {
  return CompositeOperatorName(
      CompositeOperatorFromSkia(GetState().GlobalComposite()),
      BlendModeFromSkia(GetState().GlobalComposite()));
}
