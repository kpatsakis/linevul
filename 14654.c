void HTMLInputElement::reportMemoryUsage(MemoryObjectInfo* memoryObjectInfo) const
{
    MemoryClassInfo info(memoryObjectInfo, this, WebCoreMemoryTypes::DOM);
    HTMLTextFormControlElement::reportMemoryUsage(memoryObjectInfo);
    info.addMember(m_name, "name");
    info.addMember(m_valueIfDirty, "valueIfDirty");
    info.addMember(m_suggestedValue, "suggestedValue");
    info.addMember(m_inputType, "inputType");
    info.addMember(m_listAttributeTargetObserver, "listAttributeTargetObserver");
}
