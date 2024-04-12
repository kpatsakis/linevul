bool HTMLCanvasElement::WouldTaintOrigin() const {
  return !OriginClean();
}
