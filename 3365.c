void RenderFrameHostImpl::OnForwardResourceTimingToParent(
    const ResourceTimingInfo& resource_timing) {
  if (!is_active())
    return;

  RenderFrameProxyHost* proxy =
      frame_tree_node()->render_manager()->GetProxyToParent();
  if (!proxy) {
    bool is_current = IsCurrent();
    bool has_parent = GetParent();
    bool has_parent_ftn = frame_tree_node()->parent();
    base::debug::Alias(&is_current);
    base::debug::Alias(&has_parent);
    base::debug::Alias(&has_parent_ftn);

    bool parent_is_current = false;
    bool parent_is_related_site_instance = false;
    bool parent_is_top = false;
    int32_t parent_site_instance_id = -1;
    DEBUG_ALIAS_FOR_GURL(
        parent_site_url,
        has_parent ? GetParent()->GetSiteInstance()->GetSiteURL() : GURL());
    if (has_parent) {
      parent_is_current = GetParent()->IsCurrent();
      parent_is_related_site_instance =
          GetSiteInstance()->IsRelatedSiteInstance(
              GetParent()->GetSiteInstance());
      parent_is_top = !GetParent()->GetParent();
      parent_site_instance_id = GetParent()->GetSiteInstance()->GetId();
    }
    base::debug::Alias(&parent_is_current);
    base::debug::Alias(&parent_is_related_site_instance);
    base::debug::Alias(&parent_is_top);
    base::debug::Alias(&parent_site_instance_id);

    bool parent_ftn_is_related_site_instance = false;
    int32_t parent_ftn_site_instance_id = -1;
    DEBUG_ALIAS_FOR_GURL(parent_ftn_site_url, frame_tree_node()->parent()
                                                  ? frame_tree_node()
                                                        ->parent()
                                                        ->render_manager()
                                                        ->current_frame_host()
                                                        ->GetSiteInstance()
                                                        ->GetSiteURL()
                                                  : GURL());
    bool parent_ftn_has_speculative_rfh = false;
    int32_t parent_ftn_speculative_site_instance_id = -1;
    if (has_parent_ftn) {
      parent_is_related_site_instance =
          GetSiteInstance()->IsRelatedSiteInstance(frame_tree_node()
                                                       ->parent()
                                                       ->render_manager()
                                                       ->current_frame_host()
                                                       ->GetSiteInstance());

      parent_ftn_has_speculative_rfh = frame_tree_node()
                                           ->parent()
                                           ->render_manager()
                                           ->speculative_frame_host();
      if (parent_ftn_has_speculative_rfh) {
        parent_ftn_speculative_site_instance_id = frame_tree_node()
                                                      ->parent()
                                                      ->render_manager()
                                                      ->speculative_frame_host()
                                                      ->GetSiteInstance()
                                                      ->GetId();
      }
    }
    base::debug::Alias(&parent_ftn_is_related_site_instance);
    base::debug::Alias(&parent_ftn_site_instance_id);
    base::debug::Alias(&parent_ftn_has_speculative_rfh);
    base::debug::Alias(&parent_ftn_speculative_site_instance_id);

    bool is_speculative =
        frame_tree_node()->render_manager()->speculative_frame_host() == this;
    int32_t site_instance_id = GetSiteInstance()->GetId();
    DEBUG_ALIAS_FOR_GURL(ftn_site_url, GetSiteInstance()->GetSiteURL());
    base::debug::Alias(&is_speculative);
    base::debug::Alias(&site_instance_id);

    bool ftn_has_speculative_rfh =
        frame_tree_node()->render_manager()->speculative_frame_host();
    int32_t speculative_site_instance_id = -1;
    if (ftn_has_speculative_rfh) {
      speculative_site_instance_id = frame_tree_node()
                                         ->render_manager()
                                         ->speculative_frame_host()
                                         ->GetSiteInstance()
                                         ->GetId();
    }
    base::debug::Alias(&ftn_has_speculative_rfh);
    base::debug::Alias(&speculative_site_instance_id);

    bool rvh_is_active = render_view_host()->is_active();
    bool rvh_is_live = render_view_host()->IsRenderViewLive();
    base::debug::Alias(&rvh_is_active);
    base::debug::Alias(&rvh_is_live);

    bool is_root = frame_tree_node()->frame_tree()->root() == frame_tree_node();
    base::debug::Alias(&is_root);

    bool root_rvh_is_active = frame_tree_node()
                                  ->frame_tree()
                                  ->root()
                                  ->current_frame_host()
                                  ->render_view_host()
                                  ->is_active();
    bool root_rvh_is_live = frame_tree_node()
                                ->frame_tree()
                                ->root()
                                ->current_frame_host()
                                ->render_view_host()
                                ->IsRenderViewLive();
    bool root_rvh_is_waiting_for_close_ack = frame_tree_node()
                                                 ->frame_tree()
                                                 ->root()
                                                 ->current_frame_host()
                                                 ->render_view_host()
                                                 ->is_waiting_for_close_ack();
    base::debug::Alias(&root_rvh_is_active);
    base::debug::Alias(&root_rvh_is_live);
    base::debug::Alias(&root_rvh_is_waiting_for_close_ack);

    bad_message::ReceivedBadMessage(GetProcess(),
                                    bad_message::RFH_NO_PROXY_TO_PARENT);
    return;
  }
  proxy->Send(new FrameMsg_ForwardResourceTimingToParent(proxy->GetRoutingID(),
                                                         resource_timing));
}
