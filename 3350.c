void RenderFrameHostImpl::NavigateToInterstitialURL(const GURL& data_url) {
  TRACE_EVENT1("navigation", "RenderFrameHostImpl::NavigateToInterstitialURL",
               "frame_tree_node", frame_tree_node_->frame_tree_node_id());
  DCHECK(data_url.SchemeIs(url::kDataScheme));
  CommonNavigationParams common_params(
      data_url, Referrer(), ui::PAGE_TRANSITION_LINK,
      FrameMsg_Navigate_Type::DIFFERENT_DOCUMENT, false, false,
      base::TimeTicks::Now(), FrameMsg_UILoadMetricsReportType::NO_REPORT,
      GURL(), GURL(), PREVIEWS_OFF, base::TimeTicks::Now(), "GET", nullptr,
      base::Optional<SourceLocation>(),
      CSPDisposition::CHECK /* should_check_main_world_csp */,
      false /* started_from_context_menu */, false /* has_user_gesture */,
      base::nullopt /* suggested_filename */);
  CommitNavigation(nullptr, network::mojom::URLLoaderClientEndpointsPtr(),
                   common_params, RequestNavigationParams(), false,
                   base::nullopt, base::nullopt /* subresource_overrides */,
                   base::UnguessableToken::Create() /* not traced */);
}
