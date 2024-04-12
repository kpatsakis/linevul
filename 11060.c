bool AXLayoutObject::isReadOnly() const {
  ASSERT(m_layoutObject);

  if (isWebArea()) {
    Document& document = m_layoutObject->document();
    HTMLElement* body = document.body();
    if (body && hasEditableStyle(*body)) {
      AXObject* axBody = axObjectCache().getOrCreate(body);
      return !axBody || axBody == axBody->ariaHiddenRoot();
    }

    return !hasEditableStyle(document);
  }

  return AXNodeObject::isReadOnly();
}
