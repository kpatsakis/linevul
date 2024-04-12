RenderFrameImpl::CreateWorkerFetchContext() {
  blink::WebServiceWorkerNetworkProvider* web_provider =
      frame_->GetDocumentLoader()->GetServiceWorkerNetworkProvider();
  DCHECK(web_provider);
  ServiceWorkerNetworkProvider* provider =
      ServiceWorkerNetworkProvider::FromWebServiceWorkerNetworkProvider(
          web_provider);
  mojom::ServiceWorkerWorkerClientRequest service_worker_client_request;
  mojom::ServiceWorkerContainerHostPtrInfo container_host_ptr_info;
  ServiceWorkerProviderContext* provider_context = provider->context();
  if (provider_context) {
    service_worker_client_request =
        provider_context->CreateWorkerClientRequest();
    if (ServiceWorkerUtils::IsServicificationEnabled())
      container_host_ptr_info = provider_context->CloneContainerHostPtrInfo();
  }

  std::unique_ptr<WorkerFetchContextImpl> worker_fetch_context =
      std::make_unique<WorkerFetchContextImpl>(
          std::move(service_worker_client_request),
          std::move(container_host_ptr_info), GetLoaderFactoryBundle()->Clone(),
          GetContentClient()->renderer()->CreateURLLoaderThrottleProvider(
              URLLoaderThrottleProviderType::kWorker));

  worker_fetch_context->set_parent_frame_id(routing_id_);
  worker_fetch_context->set_site_for_cookies(
      frame_->GetDocument().SiteForCookies());
  worker_fetch_context->set_is_secure_context(
      frame_->GetDocument().IsSecureContext());
  worker_fetch_context->set_service_worker_provider_id(provider->provider_id());
  worker_fetch_context->set_is_controlled_by_service_worker(
      provider->IsControlledByServiceWorker());
  worker_fetch_context->set_origin_url(
      GURL(frame_->GetDocument().Url()).GetOrigin());
  {
    SCOPED_UMA_HISTOGRAM_TIMER(
        "RenderFrameObservers.WillCreateWorkerFetchContext");
    for (auto& observer : observers_)
      observer.WillCreateWorkerFetchContext(worker_fetch_context.get());
  }
  return std::move(worker_fetch_context);
}
