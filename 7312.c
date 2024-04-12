void WebGLRenderingContextBase::ForceNextWebGLContextCreationToFail() {
  g_should_fail_context_creation_for_testing = true;
}
