    bool shouldApplyWrappingStyle(Node* node) const
    {
        return m_highestNodeToBeSerialized && m_highestNodeToBeSerialized->parentNode() == node->parentNode()
            && m_wrappingStyle && m_wrappingStyle->style();
    }
