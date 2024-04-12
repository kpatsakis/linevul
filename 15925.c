void SerializedScriptValue::registerMemoryAllocatedWithCurrentScriptContext()
{
    if (m_externallyAllocatedMemory)
        return;
    m_externallyAllocatedMemory = static_cast<intptr_t>(m_data.length());
    v8::Isolate::GetCurrent()->AdjustAmountOfExternalAllocatedMemory(m_externallyAllocatedMemory);
}
