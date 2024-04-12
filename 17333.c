void ServiceWorkerHandler::OnWorkerVersionUpdated(
    const std::vector<ServiceWorkerVersionInfo>& versions) {
  using Version = ServiceWorker::ServiceWorkerVersion;
  std::unique_ptr<protocol::Array<Version>> result =
      protocol::Array<Version>::create();
  for (const auto& version : versions) {
    base::flat_set<std::string> client_set;

    for (const auto& client : version.clients) {
      if (client.second.type ==
          blink::mojom::ServiceWorkerProviderType::kForWindow) {
        WebContents* web_contents =
            client.second.web_contents_getter
                ? client.second.web_contents_getter.Run()
                : WebContents::FromRenderFrameHost(RenderFrameHostImpl::FromID(
                      client.second.process_id, client.second.route_id));
        if (!web_contents)
          continue;
        client_set.insert(
            DevToolsAgentHost::GetOrCreateFor(web_contents)->GetId());
      }
    }
    std::unique_ptr<protocol::Array<std::string>> clients =
        protocol::Array<std::string>::create();
    for (auto& c : client_set)
      clients->addItem(c);

    std::unique_ptr<Version> version_value = Version::Create()
        .SetVersionId(base::Int64ToString(version.version_id))
        .SetRegistrationId(
            base::Int64ToString(version.registration_id))
        .SetScriptURL(version.script_url.spec())
        .SetRunningStatus(
            GetVersionRunningStatusString(version.running_status))
        .SetStatus(GetVersionStatusString(version.status))
        .SetScriptLastModified(
            version.script_last_modified.ToDoubleT())
        .SetScriptResponseTime(
            version.script_response_time.ToDoubleT())
        .SetControlledClients(std::move(clients))
        .Build();
    scoped_refptr<DevToolsAgentHostImpl> host(
        ServiceWorkerDevToolsManager::GetInstance()
            ->GetDevToolsAgentHostForWorker(
                version.process_id,
                version.devtools_agent_route_id));
    if (host)
      version_value->SetTargetId(host->GetId());
    result->addItem(std::move(version_value));
  }
  frontend_->WorkerVersionUpdated(std::move(result));
}
