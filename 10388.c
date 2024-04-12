CanvasResourceDispatcher* HTMLCanvasElement::GetOrCreateResourceDispatcher() {
  return frame_dispatcher_.get();
}
