WebGLSampler* WebGL2RenderingContextBase::createSampler() {
  if (isContextLost())
    return nullptr;
  return WebGLSampler::Create(this);
}
