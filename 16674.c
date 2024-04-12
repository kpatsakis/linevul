Node* Document::cloneNode(bool deep, ExceptionState&) {
  Document* clone = CloneDocumentWithoutChildren();
  clone->CloneDataFromDocument(*this);
  if (deep)
    CloneChildNodes(clone);
  return clone;
}
