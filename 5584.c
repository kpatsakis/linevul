void HTMLCanvasElement::AddListener(CanvasDrawListener* listener) {
  listeners_.insert(listener);
}
