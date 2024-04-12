static LayoutRect LocalToAbsolute(const LayoutBox& box, LayoutRect rect) {
  return LayoutRect(
      box.LocalToAbsoluteQuad(FloatQuad(FloatRect(rect)), kUseTransforms)
          .BoundingBox());
}
