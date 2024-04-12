AXNodeObject::AXNodeObject(Node* node, AXObjectCacheImpl& axObjectCache)
    : AXObject(axObjectCache),
      m_ariaRole(UnknownRole),
      m_childrenDirty(false),
      m_node(node) {
}
