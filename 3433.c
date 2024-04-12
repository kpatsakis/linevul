void InspectorClientImpl::dumpUncountedAllocatedObjects(const HashMap<const void*, size_t>& map)
{
    if (WebDevToolsAgentImpl* agent = devToolsAgent())
        agent->dumpUncountedAllocatedObjects(map);
}
