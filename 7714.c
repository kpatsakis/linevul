RenderFrameHostManager::GetSiteInstanceForNavigation(
    const GURL& dest_url,
    SiteInstance* source_instance,
    SiteInstance* dest_instance,
    SiteInstance* candidate_instance,
    ui::PageTransition transition,
    bool dest_is_restore,
    bool dest_is_view_source_mode,
    bool was_server_redirect) {
  DCHECK(!source_instance || !dest_instance);

  SiteInstance* current_instance = render_frame_host_->GetSiteInstance();

  if (current_instance->GetSiteURL().SchemeIs(kGuestScheme))
    return current_instance;

  const NavigationEntry* current_entry =
      delegate_->GetLastCommittedNavigationEntryForRenderManager();
  BrowserContext* browser_context =
      delegate_->GetControllerForRenderManager().GetBrowserContext();
  const GURL& current_effective_url = current_entry ?
      SiteInstanceImpl::GetEffectiveURL(browser_context,
                                        current_entry->GetURL()) :
      render_frame_host_->GetSiteInstance()->GetSiteURL();
  bool current_is_view_source_mode = current_entry ?
      current_entry->IsViewSourceMode() : dest_is_view_source_mode;
  bool force_swap = ShouldSwapBrowsingInstancesForNavigation(
      current_effective_url,
      current_is_view_source_mode,
      dest_instance,
      SiteInstanceImpl::GetEffectiveURL(browser_context, dest_url),
      dest_is_view_source_mode);
  SiteInstanceDescriptor new_instance_descriptor =
      SiteInstanceDescriptor(current_instance);
  if (ShouldTransitionCrossSite() || force_swap) {
    new_instance_descriptor = DetermineSiteInstanceForURL(
        dest_url, source_instance, current_instance, dest_instance, transition,
        dest_is_restore, dest_is_view_source_mode, force_swap,
        was_server_redirect);
  }

  scoped_refptr<SiteInstance> new_instance =
      ConvertToSiteInstance(new_instance_descriptor, candidate_instance);
  if (force_swap)
    CHECK_NE(new_instance, current_instance);

  DCHECK_EQ(new_instance->GetBrowserContext(), browser_context);

  SiteInstanceImpl* new_instance_impl =
      static_cast<SiteInstanceImpl*>(new_instance.get());
  auto* policy = ChildProcessSecurityPolicyImpl::GetInstance();
  if (!frame_tree_node_->IsMainFrame() && !new_instance_impl->HasProcess() &&
      new_instance_impl->HasSite() &&
      policy->IsIsolatedOrigin(url::Origin(new_instance_impl->GetSiteURL()))) {
    new_instance_impl->set_process_reuse_policy(
        SiteInstanceImpl::ProcessReusePolicy::REUSE_PENDING_OR_COMMITTED_SITE);
  }

  return new_instance;
}
