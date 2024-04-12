void BaseRenderingContext2D::setCurrentTransform(
    SVGMatrixTearOff* matrix_tear_off) {
  const AffineTransform& transform = matrix_tear_off->Value();
  setTransform(transform.A(), transform.B(), transform.C(), transform.D(),
               transform.E(), transform.F());
}
