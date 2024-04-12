    void reportCall(ConsoleAPIType type, const std::vector<v8::Local<v8::Value>>& arguments)
    {
        InspectedContext* inspectedContext = ensureInspectedContext();
        if (!inspectedContext)
            return;
        V8InspectorImpl* inspector = inspectedContext->inspector();
        std::unique_ptr<V8ConsoleMessage> message = V8ConsoleMessage::createForConsoleAPI(inspector->client()->currentTimeMS(), type, arguments, inspector->debugger()->captureStackTrace(false), inspectedContext);
        inspector->ensureConsoleMessageStorage(inspectedContext->contextGroupId())->addMessage(std::move(message));
    }
