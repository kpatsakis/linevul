    V8InspectorSessionImpl* currentSession()
    {
        InspectedContext* inspectedContext = ensureInspectedContext();
        if (!inspectedContext)
            return nullptr;
        return inspectedContext->inspector()->sessionForContextGroup(inspectedContext->contextGroupId());
    }
