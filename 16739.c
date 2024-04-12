SkiaOutputSurfaceImpl::SkiaOutputSurfaceImpl(
    util::PassKey<SkiaOutputSurfaceImpl> /* pass_key */,
    std::unique_ptr<SkiaOutputSurfaceDependency> deps,
    const RendererSettings& renderer_settings)
    : dependency_(std::move(deps)),
      is_using_vulkan_(dependency_->IsUsingVulkan()),
      renderer_settings_(renderer_settings) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
}
