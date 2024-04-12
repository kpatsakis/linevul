WebGLRenderingContextBase::CreateContextProviderInternal(
    CanvasRenderingContextHost* host,
    const CanvasContextCreationAttributes& attributes,
    unsigned web_gl_version,
    bool* using_gpu_compositing) {
  DCHECK(host);
  ExecutionContext* execution_context = host->GetTopExecutionContext();
  DCHECK(execution_context);

  Platform::ContextAttributes context_attributes = ToPlatformContextAttributes(
      attributes, web_gl_version,
      SupportOwnOffscreenSurface(execution_context));

  Platform::GraphicsInfo gl_info;
  std::unique_ptr<WebGraphicsContext3DProvider> context_provider;
  const auto& url = execution_context->Url();
  if (IsMainThread()) {
    *using_gpu_compositing = !Platform::Current()->IsGpuCompositingDisabled();
    context_provider =
        Platform::Current()->CreateOffscreenGraphicsContext3DProvider(
            context_attributes, url, nullptr, &gl_info);
  } else {
    context_provider = CreateContextProviderOnWorkerThread(
        context_attributes, &gl_info, using_gpu_compositing, url);
  }
  if (context_provider && !context_provider->BindToCurrentThread()) {
    context_provider = nullptr;
    gl_info.error_message =
        String("bindToCurrentThread failed: " + String(gl_info.error_message));
  }
  if (!context_provider || g_should_fail_context_creation_for_testing) {
    g_should_fail_context_creation_for_testing = false;
    host->HostDispatchEvent(WebGLContextEvent::Create(
        EventTypeNames::webglcontextcreationerror, false, true,
        ExtractWebGLContextCreationError(gl_info)));
    return nullptr;
  }
  gpu::gles2::GLES2Interface* gl = context_provider->ContextGL();
  if (!String(gl->GetString(GL_EXTENSIONS))
           .Contains("GL_OES_packed_depth_stencil")) {
    host->HostDispatchEvent(WebGLContextEvent::Create(
        EventTypeNames::webglcontextcreationerror, false, true,
        "OES_packed_depth_stencil support is required."));
    return nullptr;
  }
  return context_provider;
}
