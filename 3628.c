SkFilterQuality HTMLCanvasElement::FilterQuality() const {
  if (!isConnected())
    return kLow_SkFilterQuality;

  const ComputedStyle* style = GetComputedStyle();
  if (!style) {
    GetDocument().UpdateStyleAndLayoutTreeForNode(this);
    HTMLCanvasElement* non_const_this = const_cast<HTMLCanvasElement*>(this);
    style = non_const_this->EnsureComputedStyle();
  }
  return (style && style->ImageRendering() == EImageRendering::kPixelated)
             ? kNone_SkFilterQuality
             : kLow_SkFilterQuality;
}
