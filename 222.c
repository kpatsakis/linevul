PassRefPtrWillBeRawPtr<NameNodeList> ContainerNode::getElementsByName(const AtomicString& elementName)
{
    return ensureCachedCollection<NameNodeList>(NameNodeListType, elementName);
}
