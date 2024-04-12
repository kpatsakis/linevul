Response TargetHandler::ActivateTarget(const std::string& target_id) {
  scoped_refptr<DevToolsAgentHost> agent_host(
      DevToolsAgentHost::GetForId(target_id));
  if (!agent_host)
    return Response::InvalidParams("No target with given id found");
  agent_host->Activate();
  return Response::OK();
}
