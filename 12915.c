void RenderFrameHostImpl::RegisterMojoInterfaces() {
#if !defined(OS_ANDROID)
  registry_->AddInterface(base::Bind(&InstalledAppProviderImplDefault::Create));
#endif  // !defined(OS_ANDROID)

  PermissionManager* permission_manager =
      GetProcess()->GetBrowserContext()->GetPermissionManager();

  if (delegate_) {
    auto* geolocation_context = delegate_->GetGeolocationContext();
    if (geolocation_context && permission_manager) {
      geolocation_service_.reset(new GeolocationServiceImpl(
          geolocation_context, permission_manager, this));
      registry_->AddInterface(
          base::Bind(&GeolocationServiceImpl::Bind,
                     base::Unretained(geolocation_service_.get())));
    }
  }

  registry_->AddInterface<device::mojom::WakeLock>(base::Bind(
      &RenderFrameHostImpl::BindWakeLockRequest, base::Unretained(this)));

#if defined(OS_ANDROID)
  if (base::FeatureList::IsEnabled(features::kWebNfc)) {
    registry_->AddInterface<device::mojom::NFC>(base::Bind(
        &RenderFrameHostImpl::BindNFCRequest, base::Unretained(this)));
  }
#endif

  if (!permission_service_context_)
    permission_service_context_.reset(new PermissionServiceContext(this));

  registry_->AddInterface(
      base::Bind(&PermissionServiceContext::CreateService,
                 base::Unretained(permission_service_context_.get())));

  registry_->AddInterface(
      base::Bind(&RenderFrameHostImpl::BindPresentationServiceRequest,
                 base::Unretained(this)));

  registry_->AddInterface(
      base::Bind(&MediaSessionServiceImpl::Create, base::Unretained(this)));

#if defined(OS_ANDROID)
  registry_->AddInterface<media::mojom::Renderer>(
      base::Bind(&content::CreateMediaPlayerRenderer, GetProcess()->GetID(),
                 GetRoutingID(), delegate_));
#endif  // defined(OS_ANDROID)

  registry_->AddInterface(base::Bind(
      base::IgnoreResult(&RenderFrameHostImpl::CreateWebBluetoothService),
      base::Unretained(this)));

  registry_->AddInterface(base::BindRepeating(
      &RenderFrameHostImpl::CreateUsbDeviceManager, base::Unretained(this)));

  registry_->AddInterface(base::BindRepeating(
      &RenderFrameHostImpl::CreateUsbChooserService, base::Unretained(this)));

  registry_->AddInterface<media::mojom::InterfaceFactory>(
      base::Bind(&RenderFrameHostImpl::BindMediaInterfaceFactoryRequest,
                 base::Unretained(this)));

  registry_->AddInterface(base::Bind(&WebSocketManager::CreateWebSocket,
                                     process_->GetID(), routing_id_));

  registry_->AddInterface(base::Bind(&SharedWorkerConnectorImpl::Create,
                                     process_->GetID(), routing_id_));

  registry_->AddInterface<device::mojom::VRService>(base::Bind(
      &WebvrServiceProvider::BindWebvrService, base::Unretained(this)));

  if (RenderFrameAudioInputStreamFactory::UseMojoFactories()) {
    registry_->AddInterface(
        base::BindRepeating(&RenderFrameHostImpl::CreateAudioInputStreamFactory,
                            base::Unretained(this)));
  }

  if (RendererAudioOutputStreamFactoryContextImpl::UseMojoFactories()) {
    registry_->AddInterface(base::BindRepeating(
        &RenderFrameHostImpl::CreateAudioOutputStreamFactory,
        base::Unretained(this)));
  }

  if (resource_coordinator::IsResourceCoordinatorEnabled()) {
    registry_->AddInterface(
        base::Bind(&CreateFrameResourceCoordinator, base::Unretained(this)));
  }

#if BUILDFLAG(ENABLE_WEBRTC)
  if (BrowserMainLoop::GetInstance()) {
    MediaStreamManager* media_stream_manager =
        BrowserMainLoop::GetInstance()->media_stream_manager();
    registry_->AddInterface(
        base::Bind(&MediaDevicesDispatcherHost::Create, GetProcess()->GetID(),
                   GetRoutingID(),
                   base::Unretained(media_stream_manager)),
        BrowserThread::GetTaskRunnerForThread(BrowserThread::IO));
  }
#endif

#if BUILDFLAG(ENABLE_MEDIA_REMOTING)
  registry_->AddInterface(base::Bind(&RemoterFactoryImpl::Bind,
                                     GetProcess()->GetID(), GetRoutingID()));
#endif  // BUILDFLAG(ENABLE_MEDIA_REMOTING)

  registry_->AddInterface(base::Bind(
      &KeyboardLockServiceImpl::CreateMojoService, base::Unretained(this)));

  registry_->AddInterface(base::Bind(&ImageCaptureImpl::Create));

#if !defined(OS_ANDROID)
  if (base::FeatureList::IsEnabled(features::kWebAuth)) {
    registry_->AddInterface(
        base::Bind(&RenderFrameHostImpl::BindAuthenticatorRequest,
                   base::Unretained(this)));
  }
#endif  // !defined(OS_ANDROID)

  if (permission_manager) {
    sensor_provider_proxy_.reset(
        new SensorProviderProxyImpl(permission_manager, this));
    registry_->AddInterface(
        base::Bind(&SensorProviderProxyImpl::Bind,
                   base::Unretained(sensor_provider_proxy_.get())));
  }

  registry_->AddInterface(base::BindRepeating(
      &media::MediaMetricsProvider::Create,
      GetSiteInstance()->GetBrowserContext()->IsOffTheRecord()
          ? nullptr
          : GetSiteInstance()
                ->GetBrowserContext()
                ->GetVideoDecodePerfHistory()));

  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          cc::switches::kEnableGpuBenchmarking)) {
    registry_->AddInterface(
        base::Bind(&InputInjectorImpl::Create, weak_ptr_factory_.GetWeakPtr()));
  }

  registry_->AddInterface(
      base::BindRepeating(GetRestrictedCookieManager, base::Unretained(this)));

  registry_->AddInterface(base::BindRepeating(
      &QuotaDispatcherHost::CreateForFrame, GetProcess(), routing_id_));
}
