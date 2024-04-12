void BrowserViewRenderer::SetDipScale(float dip_scale) {
  dip_scale_ = dip_scale;
  CHECK_GT(dip_scale_, 0.f);
}
