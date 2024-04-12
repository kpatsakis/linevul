bool HTMLCanvasElement::IsAccelerated() const {
  return context_ && context_->IsAccelerated();
}
