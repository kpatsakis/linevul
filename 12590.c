void RenderViewTest::RendererBlinkPlatformImplTestOverride::Shutdown() {
  renderer_scheduler_->Shutdown();
  blink_platform_impl_->Shutdown();
}
