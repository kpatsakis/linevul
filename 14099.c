void RenderViewTest::SetUp() {
  test_io_thread_ =
      std::make_unique<base::TestIOThread>(base::TestIOThread::kAutoStart);
  ipc_support_ = std::make_unique<mojo::edk::ScopedIPCSupport>(
      test_io_thread_->task_runner(),
      mojo::edk::ScopedIPCSupport::ShutdownPolicy::FAST);

  if (!render_thread_)
    render_thread_ = std::make_unique<MockRenderThread>();

  blink_platform_impl_.Initialize();
  service_manager::BinderRegistry empty_registry;
  blink::Initialize(blink_platform_impl_.Get(), &empty_registry);

  content_client_.reset(CreateContentClient());
  content_browser_client_.reset(CreateContentBrowserClient());
  content_renderer_client_.reset(CreateContentRendererClient());
  SetContentClient(content_client_.get());
  SetBrowserClientForTesting(content_browser_client_.get());
  SetRendererClientForTesting(content_renderer_client_.get());

#if defined(OS_WIN)
  SetDWriteFontProxySenderForTesting(CreateFakeCollectionSender());
#endif

#if defined(OS_MACOSX)
  autorelease_pool_ = std::make_unique<base::mac::ScopedNSAutoreleasePool>();
#endif
  command_line_ =
      std::make_unique<base::CommandLine>(base::CommandLine::NO_PROGRAM);
  field_trial_list_ = std::make_unique<base::FieldTrialList>(nullptr);
  base::FieldTrialList::CreateTrialsFromCommandLine(
      *command_line_, switches::kFieldTrialHandle, -1);
  params_ = std::make_unique<MainFunctionParams>(*command_line_);
  platform_ = std::make_unique<RendererMainPlatformDelegate>(*params_);
  platform_->PlatformInitialize();

  std::string flags("--expose-gc");
  v8::V8::SetFlagsFromString(flags.c_str(), static_cast<int>(flags.size()));

  RenderThreadImpl::RegisterSchemes();

  RenderThreadImpl::SetRendererBlinkPlatformImplForTesting(
      blink_platform_impl_.Get());

  if (!ui::ResourceBundle::HasSharedInstance()) {
    ui::ResourceBundle::InitSharedInstanceWithLocale(
        "en-US", nullptr, ui::ResourceBundle::DO_NOT_LOAD_COMMON_RESOURCES);
  }

  compositor_deps_ = std::make_unique<FakeCompositorDependencies>();
  mock_process_ = std::make_unique<MockRenderProcess>();

  mojom::CreateViewParamsPtr view_params = mojom::CreateViewParams::New();
  view_params->opener_frame_route_id = MSG_ROUTING_NONE;
  view_params->window_was_created_with_opener = false;
  view_params->renderer_preferences = RendererPreferences();
  view_params->web_preferences = WebPreferences();
  view_params->view_id = render_thread_->GetNextRoutingID();
  view_params->main_frame_widget_routing_id = view_params->view_id;
  view_params->main_frame_routing_id = render_thread_->GetNextRoutingID();
  render_thread_->PassInitialInterfaceProviderRequestForFrame(
      view_params->main_frame_routing_id,
      mojo::MakeRequest(&view_params->main_frame_interface_provider));
  view_params->session_storage_namespace_id = kInvalidSessionStorageNamespaceId;
  view_params->swapped_out = false;
  view_params->replicated_frame_state = FrameReplicationState();
  view_params->proxy_routing_id = MSG_ROUTING_NONE;
  view_params->hidden = false;
  view_params->never_visible = false;
  view_params->initial_size = *InitialSizeParams();
  view_params->enable_auto_resize = false;
  view_params->min_size = gfx::Size();
  view_params->max_size = gfx::Size();

  view_ = RenderViewImpl::Create(compositor_deps_.get(), std::move(view_params),
                                 RenderWidget::ShowCallback(),
                                 base::ThreadTaskRunnerHandle::Get());
}
