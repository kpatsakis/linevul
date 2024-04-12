void LocalDOMWindow::SendOrientationChangeEvent() {
  DCHECK(RuntimeEnabledFeatures::OrientationEventEnabled());
  DCHECK(GetFrame()->IsLocalRoot());

  HeapVector<Member<LocalFrame>> frames;
  frames.push_back(GetFrame());
  for (size_t i = 0; i < frames.size(); i++) {
    for (Frame* child = frames[i]->Tree().FirstChild(); child;
         child = child->Tree().NextSibling()) {
      if (child->IsLocalFrame())
        frames.push_back(ToLocalFrame(child));
    }
  }

  for (LocalFrame* frame : frames) {
    frame->DomWindow()->DispatchEvent(
        Event::Create(EventTypeNames::orientationchange));
  }
}
