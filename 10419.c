void CreateProcessResourceCoordinator(
    RenderProcessHostImpl* render_process_host,
    resource_coordinator::mojom::ProcessCoordinationUnitRequest request) {
  render_process_host->GetProcessResourceCoordinator()->AddBinding(
      std::move(request));
}
