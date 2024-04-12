void Document::statePopped(PassRefPtr<SerializedScriptValue> stateObject)
{
    if (!frame())
        return;

    if (m_readyState == Complete)
        enqueuePopstateEvent(stateObject);
    else
        m_pendingStateObject = stateObject;
}
