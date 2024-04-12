void SVGElement::RemovedFrom(ContainerNode& root_parent) {
  bool was_in_document = root_parent.isConnected();

  if (was_in_document && HasRelativeLengths()) {
    if (root_parent.IsSVGElement() && !parentNode()) {
      DCHECK(ToSVGElement(root_parent)
                 .elements_with_relative_lengths_.Contains(this));
      ToSVGElement(root_parent).UpdateRelativeLengthsInformation(false, this);
    }

    elements_with_relative_lengths_.clear();
  }

  SECURITY_DCHECK(!root_parent.IsSVGElement() ||
                  !ToSVGElement(root_parent)
                       .elements_with_relative_lengths_.Contains(this));

  Element::RemovedFrom(root_parent);

  if (was_in_document) {
    RebuildAllIncomingReferences();
    RemoveAllIncomingReferences();
  }

  InvalidateInstances();
}
