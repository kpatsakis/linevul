void RenderViewHostImpl::OnOpenURL(
    const ViewHostMsg_OpenURL_Params& params) {
  GURL validated_url(params.url);
  FilterURL(ChildProcessSecurityPolicyImpl::GetInstance(),
            GetProcess(), false, &validated_url);

  delegate_->RequestOpenURL(
      this, validated_url, params.referrer, params.disposition, params.frame_id,
      params.is_cross_site_redirect);
}
