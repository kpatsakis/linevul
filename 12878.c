unsigned AXTableCell::ariaRowIndex() const {
  const AtomicString& rowIndex = getAttribute(aria_rowindexAttr);
  if (rowIndex.toInt() >= 1)
    return rowIndex.toInt();

  AXObject* parent = parentObjectUnignored();
  if (!parent || !parent->isTableRow())
    return 0;

  return toAXTableRow(parent)->ariaRowIndex();
}
