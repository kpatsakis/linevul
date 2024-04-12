void InspectorClientImpl::stopGPUEventsRecording()
{
    if (WebDevToolsAgentImpl* agent = devToolsAgent())
        agent->stopGPUEventsRecording();
}
