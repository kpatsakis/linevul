void WebContentsImpl::CreateNewWindow(
    SiteInstance* source_site_instance,
    int32_t route_id,
    int32_t main_frame_route_id,
    int32_t main_frame_widget_route_id,
    const ViewHostMsg_CreateWindow_Params& params,
    SessionStorageNamespace* session_storage_namespace) {
  bool is_guest = BrowserPluginGuest::IsGuest(this);

  if (is_guest && BrowserPluginGuestMode::UseCrossProcessFramesForGuests()) {
    NOTREACHED();
  }

  DCHECK(!params.opener_suppressed || route_id == MSG_ROUTING_NONE);

  scoped_refptr<SiteInstance> site_instance =
      params.opener_suppressed && !is_guest
          ? SiteInstance::CreateForURL(GetBrowserContext(), params.target_url)
          : source_site_instance;

  int render_process_id = source_site_instance->GetProcess()->GetID();
  if (!HasMatchingProcess(&frame_tree_, render_process_id)) {
    RenderProcessHost* rph = source_site_instance->GetProcess();
    base::ProcessHandle process_handle = rph->GetHandle();
    if (process_handle != base::kNullProcessHandle) {
      RecordAction(
          base::UserMetricsAction("Terminate_ProcessMismatch_CreateNewWindow"));
      rph->Shutdown(RESULT_CODE_KILLED, false);
    }
    return;
  }

  const std::string& partition_id =
      GetContentClient()->browser()->
          GetStoragePartitionIdForSite(GetBrowserContext(),
                                       site_instance->GetSiteURL());
  StoragePartition* partition = BrowserContext::GetStoragePartition(
      GetBrowserContext(), site_instance.get());
  DOMStorageContextWrapper* dom_storage_context =
      static_cast<DOMStorageContextWrapper*>(partition->GetDOMStorageContext());
  SessionStorageNamespaceImpl* session_storage_namespace_impl =
      static_cast<SessionStorageNamespaceImpl*>(session_storage_namespace);
  CHECK(session_storage_namespace_impl->IsFromContext(dom_storage_context));

  if (delegate_ &&
      !delegate_->ShouldCreateWebContents(
          this, route_id, main_frame_route_id, main_frame_widget_route_id,
          params.window_container_type, params.frame_name, params.target_url,
          partition_id, session_storage_namespace)) {
    if (route_id != MSG_ROUTING_NONE &&
        !RenderViewHost::FromID(render_process_id, route_id)) {
      Send(new ViewMsg_Close(route_id));
    }
    ResourceDispatcherHostImpl::ResumeBlockedRequestsForRouteFromUI(
        GlobalFrameRoutingId(render_process_id, main_frame_route_id));
    return;
  }

  CreateParams create_params(GetBrowserContext(), site_instance.get());
  create_params.routing_id = route_id;
  create_params.main_frame_routing_id = main_frame_route_id;
  create_params.main_frame_widget_routing_id = main_frame_widget_route_id;
  create_params.main_frame_name = params.frame_name;
  create_params.opener_render_process_id = render_process_id;
  create_params.opener_render_frame_id = params.opener_render_frame_id;
  create_params.opener_suppressed = params.opener_suppressed;
  if (params.disposition == NEW_BACKGROUND_TAB)
    create_params.initially_hidden = true;
  create_params.renderer_initiated_creation =
      main_frame_route_id != MSG_ROUTING_NONE;

  WebContentsImpl* new_contents = NULL;
  if (!is_guest) {
    create_params.context = view_->GetNativeView();
    create_params.initial_size = GetContainerBounds().size();
    new_contents = static_cast<WebContentsImpl*>(
        WebContents::Create(create_params));
  }  else {
    new_contents = GetBrowserPluginGuest()->CreateNewGuestWindow(create_params);
  }
  new_contents->GetController().SetSessionStorageNamespace(
      partition_id,
      session_storage_namespace);

  if (!params.frame_name.empty())
    new_contents->GetRenderManager()->CreateProxiesForNewNamedFrame();

  if (!params.opener_suppressed) {
    if (!is_guest) {
      WebContentsView* new_view = new_contents->view_.get();

      new_view->CreateViewForWidget(
          new_contents->GetRenderViewHost()->GetWidget(), false);
    }
    DCHECK_NE(MSG_ROUTING_NONE, route_id);
    pending_contents_[route_id] = new_contents;
    AddDestructionObserver(new_contents);
  }

  if (delegate_) {
    delegate_->WebContentsCreated(
        this, params.opener_render_frame_id, params.frame_name,
        params.target_url, new_contents);
  }

  if (params.opener_suppressed) {
    bool was_blocked = false;
    if (delegate_) {
      gfx::Rect initial_rect;
      delegate_->AddNewContents(
          this, new_contents, params.disposition, initial_rect,
          params.user_gesture, &was_blocked);
    }
    if (!was_blocked) {
      OpenURLParams open_params(params.target_url,
                                Referrer(),
                                CURRENT_TAB,
                                ui::PAGE_TRANSITION_LINK,
                                true /* is_renderer_initiated */);
      open_params.user_gesture = params.user_gesture;

      if (delegate_ && !is_guest &&
          !delegate_->ShouldResumeRequestsForCreatedWindow()) {
        new_contents->delayed_open_url_params_.reset(
            new OpenURLParams(open_params));
      } else {
        new_contents->OpenURL(open_params);
      }
    }
  }
}
