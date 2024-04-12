void WebGLRenderingContextBase::PrintWarningToConsole(const String& message) {
  if (!canvas())
    return;
  canvas()->GetDocument().AddConsoleMessage(
      ConsoleMessage::Create(mojom::ConsoleMessageSource::kRendering,
                             mojom::ConsoleMessageLevel::kWarning, message));
}
