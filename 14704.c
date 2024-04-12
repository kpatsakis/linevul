void HTMLFrameOwnerElement::FrameOwnerPropertiesChanged() {
  if (ContentFrame()) {
    GetDocument().GetFrame()->Client()->DidChangeFrameOwnerProperties(this);
  }
}
