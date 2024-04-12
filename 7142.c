RenderViewImpl::RenderViewImpl(RenderViewImplParams* params)
    : RenderWidget(WebKit::WebPopupTypeNone,
                   params->screen_info,
                   params->swapped_out),
      webkit_preferences_(params->webkit_prefs),
      send_content_state_immediately_(false),
      enabled_bindings_(0),
      send_preferred_size_changes_(false),
      is_loading_(false),
      navigation_gesture_(NavigationGestureUnknown),
      opened_by_user_gesture_(true),
      opener_suppressed_(false),
      page_id_(-1),
      last_page_id_sent_to_browser_(-1),
      next_page_id_(params->next_page_id),
      history_list_offset_(-1),
      history_list_length_(0),
      target_url_status_(TARGET_NONE),
      selection_text_offset_(0),
      cached_is_main_frame_pinned_to_left_(false),
      cached_is_main_frame_pinned_to_right_(false),
      cached_has_main_frame_horizontal_scrollbar_(false),
      cached_has_main_frame_vertical_scrollbar_(false),
      ALLOW_THIS_IN_INITIALIZER_LIST(cookie_jar_(this)),
      geolocation_dispatcher_(NULL),
      input_tag_speech_dispatcher_(NULL),
      speech_recognition_dispatcher_(NULL),
      device_orientation_dispatcher_(NULL),
      media_stream_dispatcher_(NULL),
      browser_plugin_manager_(NULL),
      media_stream_impl_(NULL),
      devtools_agent_(NULL),
      accessibility_mode_(AccessibilityModeOff),
      renderer_accessibility_(NULL),
      java_bridge_dispatcher_(NULL),
      mouse_lock_dispatcher_(NULL),
      favicon_helper_(NULL),
#if defined(OS_ANDROID)
      body_background_color_(SK_ColorWHITE),
      update_frame_info_scheduled_(false),
      expected_content_intent_id_(0),
      media_player_proxy_(NULL),
      synchronous_find_active_match_ordinal_(-1),
      ALLOW_THIS_IN_INITIALIZER_LIST(
          load_progress_tracker_(new LoadProgressTracker(this))),
#endif
      session_storage_namespace_id_(params->session_storage_namespace_id),
      handling_select_range_(false),
      next_snapshot_id_(0),
#if defined(OS_WIN)
      focused_plugin_id_(-1),
#endif
      updating_frame_tree_(false),
      pending_frame_tree_update_(false),
      target_process_id_(0),
      target_routing_id_(0) {
#if defined(ENABLE_PLUGINS)
  pepper_helper_.reset(new PepperPluginDelegateImpl(this));
#else
  pepper_helper_.reset(new RenderViewPepperHelper());
#endif
  set_throttle_input_events(params->renderer_prefs.throttle_input_events);
  routing_id_ = params->routing_id;
  surface_id_ = params->surface_id;
  if (params->opener_id != MSG_ROUTING_NONE && params->is_renderer_created)
    opener_id_ = params->opener_id;

  DCHECK_GE(next_page_id_, 0);

#if defined(ENABLE_NOTIFICATIONS)
  notification_provider_ = new NotificationProvider(this);
#else
  notification_provider_ = NULL;
#endif

  webwidget_ = WebView::create(this);
  webwidget_mouse_lock_target_.reset(new WebWidgetLockTarget(webwidget_));

  const CommandLine& command_line = *CommandLine::ForCurrentProcess();

#if defined(OS_ANDROID)
  content::DeviceTelephonyInfo device_info;

  const std::string region_code =
      command_line.HasSwitch(switches::kNetworkCountryIso)
          ? command_line.GetSwitchValueASCII(switches::kNetworkCountryIso)
          : device_info.GetNetworkCountryIso();
  content_detectors_.push_back(linked_ptr<ContentDetector>(
      new AddressDetector()));
  content_detectors_.push_back(linked_ptr<ContentDetector>(
      new PhoneNumberDetector(region_code)));
  content_detectors_.push_back(linked_ptr<ContentDetector>(
      new EmailDetector()));
#endif

  if (params->counter) {
    shared_popup_counter_ = params->counter;
    if (!params->swapped_out)
      shared_popup_counter_->data++;
    decrement_shared_popup_at_destruction_ = true;
  } else {
    shared_popup_counter_ = new SharedRenderViewCounter(0);
    decrement_shared_popup_at_destruction_ = false;
  }

  RenderThread::Get()->AddRoute(routing_id_, this);
  AddRef();

  if (opener_id_ == MSG_ROUTING_NONE) {
    did_show_ = true;
    CompleteInit();
  }

  g_view_map.Get().insert(std::make_pair(webview(), this));
  g_routing_id_view_map.Get().insert(std::make_pair(routing_id_, this));
  webview()->setDeviceScaleFactor(device_scale_factor_);
  webkit_preferences_.Apply(webview());
  webview()->initializeMainFrame(this);

  if (command_line.HasSwitch(switches::kEnableTouchDragDrop))
    webview()->settings()->setTouchDragDropEnabled(true);

  if (!params->frame_name.empty())
    webview()->mainFrame()->setName(params->frame_name);
  webview()->settings()->setMinimumTimerInterval(
      is_hidden() ? webkit_glue::kBackgroundTabTimerInterval :
          webkit_glue::kForegroundTabTimerInterval);

  OnSetRendererPrefs(params->renderer_prefs);

#if defined(ENABLE_WEBRTC)
  if (!media_stream_dispatcher_)
    media_stream_dispatcher_ = new MediaStreamDispatcher(this);
#endif

  new MHTMLGenerator(this);
#if defined(OS_MACOSX)
  new TextInputClientObserver(this);
#endif  // defined(OS_MACOSX)

#if defined(OS_ANDROID)
  media_player_manager_.reset(
      new webkit_media::WebMediaPlayerManagerAndroid());
#endif

  devtools_agent_ = new DevToolsAgent(this);
  mouse_lock_dispatcher_ = new RenderViewMouseLockDispatcher(this);
  intents_host_ = new WebIntentsHost(this);
  favicon_helper_ = new FaviconHelper(this);

  OnSetAccessibilityMode(params->accessibility_mode);

  new IdleUserDetector(this);

  if (command_line.HasSwitch(switches::kDomAutomationController))
    enabled_bindings_ |= BINDINGS_POLICY_DOM_AUTOMATION;

  ProcessViewLayoutFlags(command_line);

  GetContentClient()->renderer()->RenderViewCreated(this);

  if (params->opener_id != MSG_ROUTING_NONE && !params->is_renderer_created) {
    RenderViewImpl* opener_view = FromRoutingID(params->opener_id);
    if (opener_view)
      webview()->mainFrame()->setOpener(opener_view->webview()->mainFrame());
  }

  if (is_swapped_out_)
    NavigateToSwappedOutURL(webview()->mainFrame());
}
