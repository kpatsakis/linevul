  void addObjectVectorAttribute(AXObjectVectorAttribute attribute,
                                HeapVector<Member<AXObject>>& objects) {
    switch (attribute) {
      case AXObjectVectorAttribute::AriaControls:
        m_properties.addItem(createRelatedNodeListProperty(
            AXRelationshipAttributesEnum::Controls, objects, aria_controlsAttr,
            *m_axObject));
        break;
      case AXObjectVectorAttribute::AriaDetails:
        m_properties.addItem(createRelatedNodeListProperty(
            AXRelationshipAttributesEnum::Details, objects, aria_controlsAttr,
            *m_axObject));
        break;
      case AXObjectVectorAttribute::AriaFlowTo:
        m_properties.addItem(createRelatedNodeListProperty(
            AXRelationshipAttributesEnum::Flowto, objects, aria_flowtoAttr,
            *m_axObject));
        break;
    }
  }
