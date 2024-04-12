void HTMLIFrameElement::Trace(blink::Visitor* visitor) {
  visitor->Trace(sandbox_);
  HTMLFrameElementBase::Trace(visitor);
  Supplementable<HTMLIFrameElement>::Trace(visitor);
}
