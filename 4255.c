void HTMLMediaElement::selectMediaResource() {
  BLINK_MEDIA_LOG << "selectMediaResource(" << (void*)this << ")";

  enum Mode { Object, Attribute, Children, Nothing };
  Mode mode = Nothing;

  if (m_srcObject) {
    mode = Object;
  } else if (fastHasAttribute(srcAttr)) {
    mode = Attribute;
  } else if (HTMLSourceElement* element =
                 Traversal<HTMLSourceElement>::firstChild(*this)) {
    mode = Children;
    m_nextChildNodeToConsider = element;
    m_currentSourceNode = nullptr;
  } else {
    m_loadState = WaitingForSource;
    setShouldDelayLoadEvent(false);
    setNetworkState(kNetworkEmpty);
    updateDisplayState();

    BLINK_MEDIA_LOG << "selectMediaResource(" << (void*)this
                    << "), nothing to load";
    return;
  }

  setNetworkState(kNetworkLoading);

  scheduleEvent(EventTypeNames::loadstart);

  switch (mode) {
    case Object:
      loadSourceFromObject();
      BLINK_MEDIA_LOG << "selectMediaResource(" << (void*)this
                      << ", using 'srcObject' attribute";
      break;
    case Attribute:
      loadSourceFromAttribute();
      BLINK_MEDIA_LOG << "selectMediaResource(" << (void*)this
                      << "), using 'src' attribute url";
      break;
    case Children:
      loadNextSourceChild();
      BLINK_MEDIA_LOG << "selectMediaResource(" << (void*)this
                      << "), using source element";
      break;
    default:
      NOTREACHED();
  }
}
