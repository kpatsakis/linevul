HTMLCanvasElement::RenderingContextFactories() {
  DCHECK(IsMainThread());
  DEFINE_STATIC_LOCAL(ContextFactoryVector, context_factories,
                      (CanvasRenderingContext::kMaxValue));
  return context_factories;
}
