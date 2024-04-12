Node* Document::adoptNode(Node* source, ExceptionState& exception_state) {
  EventQueueScope scope;

  switch (source->getNodeType()) {
    case kDocumentNode:
      exception_state.ThrowDOMException(kNotSupportedError,
                                        "The node provided is of type '" +
                                            source->nodeName() +
                                            "', which may not be adopted.");
      return nullptr;
    case kAttributeNode: {
      Attr* attr = ToAttr(source);
      if (Element* owner_element = attr->ownerElement())
        owner_element->removeAttributeNode(attr, exception_state);
      break;
    }
    default:
      if (source->IsShadowRoot()) {
        exception_state.ThrowDOMException(
            kHierarchyRequestError,
            "The node provided is a shadow root, which may not be adopted.");
        return nullptr;
      }

      if (source->IsFrameOwnerElement()) {
        HTMLFrameOwnerElement* frame_owner_element =
            ToHTMLFrameOwnerElement(source);
        if (GetFrame() && GetFrame()->Tree().IsDescendantOf(
                              frame_owner_element->ContentFrame())) {
          exception_state.ThrowDOMException(
              kHierarchyRequestError,
              "The node provided is a frame which contains this document.");
          return nullptr;
        }
      }
      if (source->parentNode()) {
        source->parentNode()->RemoveChild(source, exception_state);
        if (exception_state.HadException())
          return nullptr;
        if (source->parentNode()) {
          AddConsoleMessage(ConsoleMessage::Create(
              kJSMessageSource, kWarningMessageLevel,
              ExceptionMessages::FailedToExecute("adoptNode", "Document",
                                                 "Unable to remove the "
                                                 "specified node from the "
                                                 "original parent.")));
          return nullptr;
        }
      }
  }

  AdoptIfNeeded(*source);

  return source;
}
