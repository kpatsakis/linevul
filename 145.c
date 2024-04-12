void WebPageProxy::validateCommandCallback(const String& commandName, bool isEnabled, int state, uint64_t callbackID)
{
    RefPtr<ValidateCommandCallback> callback = m_validateCommandCallbacks.take(callbackID);
    if (!callback) {
        return;
    }

    callback->performCallbackWithReturnValue(commandName.impl(), isEnabled, state);
}
