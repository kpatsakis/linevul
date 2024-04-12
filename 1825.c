void SVGElement::SynchronizeAnimatedSVGAttribute(
    const QualifiedName& name) const {
  if (!GetElementData() ||
      !GetElementData()->animated_svg_attributes_are_dirty_)
    return;

  const_cast<SVGElement*>(this)->EnsureAttributeAnimValUpdated();

  if (name == AnyQName()) {
    AttributeToPropertyMap::const_iterator::ValuesIterator it =
        attribute_to_property_map_.Values().begin();
    AttributeToPropertyMap::const_iterator::ValuesIterator end =
        attribute_to_property_map_.Values().end();
    for (; it != end; ++it) {
      if ((*it)->NeedsSynchronizeAttribute())
        (*it)->SynchronizeAttribute();
    }

    GetElementData()->animated_svg_attributes_are_dirty_ = false;
  } else {
    SVGAnimatedPropertyBase* property = attribute_to_property_map_.at(name);
    if (property && property->NeedsSynchronizeAttribute())
      property->SynchronizeAttribute();
  }
}
