bool SVGElement::LayoutObjectIsNeeded(const ComputedStyle& style) const {
  return IsValid() && HasSVGParent() && Element::LayoutObjectIsNeeded(style);
 }
