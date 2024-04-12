const ClipPaintPropertyNode* PaintPropertyTreeBuilderTest::DocContentClip(
    const Document* document) {
  if (!document)
    document = &GetDocument();
  return document->GetLayoutView()
      ->FirstFragment()
      .PaintProperties()
      ->OverflowClip();
}
