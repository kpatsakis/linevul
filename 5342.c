void FrameLoader::UpgradeInsecureRequest(ResourceRequest& resource_request,
                                         ExecutionContext* origin_context) {

  if (!origin_context)
    return;

  if (!(origin_context->GetSecurityContext().GetInsecureRequestPolicy() &
        kUpgradeInsecureRequests))
    return;

  if (resource_request.GetFrameType() ==
      network::mojom::RequestContextFrameType::kNested) {
    return;
  }

  resource_request.SetUpgradeIfInsecure(true);

  KURL url = resource_request.Url();
  if (!url.ProtocolIs("http"))
    return;

  if (resource_request.GetFrameType() ==
          network::mojom::RequestContextFrameType::kNone ||
      resource_request.GetRequestContext() ==
          WebURLRequest::kRequestContextForm ||
      (!url.Host().IsNull() && origin_context->GetSecurityContext()
                                   .InsecureNavigationsToUpgrade()
                                   ->Contains(url.Host().Impl()->GetHash()))) {
    UseCounter::Count(origin_context,
                      WebFeature::kUpgradeInsecureRequestsUpgradedRequest);
    url.SetProtocol("https");
    if (url.Port() == 80)
      url.SetPort(443);
    resource_request.SetURL(url);
  }
}
