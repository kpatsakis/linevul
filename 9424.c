bool RenderProcessHostImpl::Init() {
  if (HasConnection())
    return true;

  is_dead_ = false;

  base::CommandLine::StringType renderer_prefix;
  const base::CommandLine& browser_command_line =
      *base::CommandLine::ForCurrentProcess();
  renderer_prefix =
      browser_command_line.GetSwitchValueNative(switches::kRendererCmdPrefix);

#if defined(OS_LINUX)
  int flags = renderer_prefix.empty() ? ChildProcessHost::CHILD_ALLOW_SELF
                                      : ChildProcessHost::CHILD_NORMAL;
#else
  int flags = ChildProcessHost::CHILD_NORMAL;
#endif

  base::FilePath renderer_path = ChildProcessHost::GetChildPath(flags);
  if (renderer_path.empty())
    return false;

  sent_render_process_ready_ = false;

  if (!channel_)
    InitializeChannelProxy();
  DCHECK(pending_connection_);

  channel_->Unpause(false /* flush */);

  GetContentClient()->browser()->RenderProcessWillLaunch(this);

#if !defined(OS_MACOSX)
  media::AudioManager::StartHangMonitorIfNeeded(
      BrowserThread::GetTaskRunnerForThread(BrowserThread::IO));
#endif  // !defined(OS_MACOSX)

#if defined(OS_ANDROID)
  static_cast<media::AudioManagerAndroid*>(media::AudioManager::Get())->
      InitializeIfNeeded();
#endif  // defined(OS_ANDROID)

  CreateMessageFilters();
  RegisterMojoInterfaces();

  if (run_renderer_in_process()) {
    DCHECK(g_renderer_main_thread_factory);
    in_process_renderer_.reset(
        g_renderer_main_thread_factory(InProcessChildThreadParams(
            BrowserThread::GetTaskRunnerForThread(BrowserThread::IO),
            child_connection_->service_token())));

    base::Thread::Options options;
#if defined(OS_WIN) && !defined(OS_MACOSX)
    options.message_loop_type = base::MessageLoop::TYPE_UI;
#else
    options.message_loop_type = base::MessageLoop::TYPE_DEFAULT;
#endif
    OnProcessLaunched();  // Fake a callback that the process is ready.

    in_process_renderer_->StartWithOptions(options);

    g_in_process_thread = in_process_renderer_->message_loop();

    channel_->Flush();
  } else {
    std::unique_ptr<base::CommandLine> cmd_line =
        base::MakeUnique<base::CommandLine>(renderer_path);
    if (!renderer_prefix.empty())
      cmd_line->PrependWrapper(renderer_prefix);
    AppendRendererCommandLine(cmd_line.get());

    child_process_launcher_.reset(new ChildProcessLauncher(
        base::MakeUnique<RendererSandboxedProcessLauncherDelegate>(),
        std::move(cmd_line), GetID(), this, std::move(pending_connection_),
        base::Bind(&RenderProcessHostImpl::OnMojoError, id_)));
    channel_->Pause();

    fast_shutdown_started_ = false;
  }

  if (!gpu_observer_registered_) {
    gpu_observer_registered_ = true;
    ui::GpuSwitchingManager::GetInstance()->AddObserver(this);
  }

  is_initialized_ = true;
  init_time_ = base::TimeTicks::Now();
  return true;
}
