WebMediaPlayer* RenderViewImpl::createMediaPlayer(
    WebFrame* frame, const WebKit::WebURL& url, WebMediaPlayerClient* client) {
  FOR_EACH_OBSERVER(
      RenderViewObserver, observers_, WillCreateMediaPlayer(frame, client));

  const CommandLine* cmd_line = CommandLine::ForCurrentProcess();
#if defined(ENABLE_WEBRTC)
  if (MediaStreamImpl::CheckMediaStream(url)) {
    EnsureMediaStreamImpl();
    return new webkit_media::WebMediaPlayerMS(
        frame, client, AsWeakPtr(), media_stream_impl_, new RenderMediaLog());
  }
#endif

#if defined(OS_ANDROID)
  GpuChannelHost* gpu_channel_host =
      RenderThreadImpl::current()->EstablishGpuChannelSync(
          CAUSE_FOR_GPU_LAUNCH_VIDEODECODEACCELERATOR_INITIALIZE);
  if (!gpu_channel_host) {
    LOG(ERROR) << "Failed to establish GPU channel for media player";
    return NULL;
  }

  scoped_refptr<cc::ContextProvider> context_provider =
      RenderThreadImpl::current()->OffscreenContextProviderForMainThread();
  if (!context_provider->InitializeOnMainThread() ||
      !context_provider->BindToCurrentThread()) {
    LOG(ERROR) << "Failed to get context3d for media player";
    return NULL;
  }

  if (cmd_line->HasSwitch(switches::kInProcessWebGL)) {
    if (!media_bridge_manager_.get()) {
      media_bridge_manager_.reset(
          new webkit_media::MediaPlayerBridgeManagerImpl(1));
    }
    return new webkit_media::WebMediaPlayerInProcessAndroid(
        frame,
        client,
        cookieJar(frame),
        media_player_manager_.get(),
        media_bridge_manager_.get(),
        new StreamTextureFactoryImpl(
            context_provider->Context3d(), gpu_channel_host, routing_id_),
        cmd_line->HasSwitch(switches::kDisableMediaHistoryLogging));
  }
  if (!media_player_proxy_) {
    media_player_proxy_ = new WebMediaPlayerProxyImplAndroid(
        this, media_player_manager_.get());
  }
  return new webkit_media::WebMediaPlayerImplAndroid(
      frame,
      client,
      media_player_manager_.get(),
      media_player_proxy_,
      new StreamTextureFactoryImpl(
          context_provider->Context3d(), gpu_channel_host, routing_id_));
#endif

  scoped_refptr<media::AudioRendererSink> sink;
  if (!cmd_line->HasSwitch(switches::kDisableAudio)) {
    if (!cmd_line->HasSwitch(switches::kDisableRendererSideMixing)) {
      sink = RenderThreadImpl::current()->GetAudioRendererMixerManager()->
          CreateInput(routing_id_);
      DVLOG(1) << "Using AudioRendererMixerManager-provided sink: " << sink;
    } else {
      scoped_refptr<RendererAudioOutputDevice> device =
          AudioDeviceFactory::NewOutputDevice();
      device->SetSourceRenderView(routing_id_);
      sink = device;
      DVLOG(1) << "Using AudioDeviceFactory-provided sink: " << sink;
    }
  }

  scoped_refptr<media::GpuVideoDecoder::Factories> gpu_factories;
  WebGraphicsContext3DCommandBufferImpl* context3d = NULL;
  if (!cmd_line->HasSwitch(switches::kDisableAcceleratedVideoDecode))
    context3d = RenderThreadImpl::current()->GetGpuVDAContext3D();
  if (context3d) {
    scoped_refptr<base::MessageLoopProxy> factories_loop =
        RenderThreadImpl::current()->compositor_message_loop_proxy();
    if (!factories_loop)
      factories_loop = base::MessageLoopProxy::current();
    GpuChannelHost* gpu_channel_host =
        RenderThreadImpl::current()->EstablishGpuChannelSync(
            CAUSE_FOR_GPU_LAUNCH_VIDEODECODEACCELERATOR_INITIALIZE);
    gpu_factories = new RendererGpuVideoDecoderFactories(
        gpu_channel_host, factories_loop, context3d);
  }

  webkit_media::WebMediaPlayerParams params(
      sink, gpu_factories, new RenderMediaLog());
  WebMediaPlayer* media_player =
      GetContentClient()->renderer()->OverrideCreateWebMediaPlayer(
          this, frame, client, AsWeakPtr(), params);
  if (!media_player) {
    media_player = new webkit_media::WebMediaPlayerImpl(
        frame, client, AsWeakPtr(), params);
  }
  return media_player;
}
