ScriptPromise Notification::requestPermission(ScriptState* scriptState, NotificationPermissionCallback* deprecatedCallback)
{
    ExecutionContext* context = scriptState->executionContext();
    if (NotificationPermissionClient* permissionClient = NotificationPermissionClient::from(context))
        return permissionClient->requestPermission(scriptState, deprecatedCallback);

    ASSERT(context->activeDOMObjectsAreStopped());
    return ScriptPromise();
}
