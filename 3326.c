void RenderFrameDevToolsAgentHost::OnNavigationRequestFailed(
    const NavigationRequest& nav_request,
    int error_code) {
  FrameTreeNode* ftn = nav_request.frame_tree_node();
  std::string id = nav_request.devtools_navigation_token().ToString();
  DispatchToAgents(ftn, &protocol::NetworkHandler::LoadingComplete, id,
                   protocol::Page::ResourceTypeEnum::Document,
                   network::URLLoaderCompletionStatus(error_code));
}
