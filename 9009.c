void RenderFrameImpl::OnAddMessageToConsole(
    blink::mojom::ConsoleMessageLevel level,
    const std::string& message) {
  AddMessageToConsole(level, message);
}
