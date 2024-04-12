bool SerializerMarkupAccumulator::shouldIgnoreAttribute(const Attribute& attribute)
{
    PageSerializer::Delegate* delegate = m_serializer->delegate();
    if (delegate)
        return delegate->shouldIgnoreAttribute(attribute);

    return MarkupAccumulator::shouldIgnoreAttribute(attribute);
}
