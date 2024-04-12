void InspectorClientImpl::getAllocatedObjects(HashSet<const void*>& set)
{
    if (WebDevToolsAgentImpl* agent = devToolsAgent())
        agent->getAllocatedObjects(set);
}
