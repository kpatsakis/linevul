bool RenderView::SupportsAsynchronousSwapBuffers() {
  WebKit::WebGraphicsContext3D* context = webview()->graphicsContext3D();
  if (!context)
    return false;
  std::string extensions(context->getRequestableExtensionsCHROMIUM().utf8());
  return extensions.find("GL_CHROMIUM_swapbuffers_complete_callback") !=
      std::string::npos;
}
