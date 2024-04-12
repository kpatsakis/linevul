void PrepareFrameAndViewForPrint::frameDetached(blink::WebFrame* frame,
                                                DetachType type) {
  DCHECK(type == DetachType::Remove);
  if (frame->parent())
    frame->parent()->removeChild(frame);
  frame->close();
}
