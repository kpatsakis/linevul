void BaseRenderingContext2D::Trace(blink::Visitor* visitor) {
  visitor->Trace(state_stack_);
}
