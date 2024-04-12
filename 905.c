WebGraphicsContext3D* RenderViewImpl::createGraphicsContext3D(
    const WebGraphicsContext3D::Attributes& attributes) {
  return createGraphicsContext3D(attributes, true);
}
