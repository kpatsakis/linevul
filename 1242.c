void InProcessBrowserTest::SetUp() {
  ASSERT_TRUE(CreateUserDataDirectory())
      << "Could not create user data directory.";

  DCHECK(g_browser_process);
  delete g_browser_process;
  g_browser_process = NULL;

  ASSERT_TRUE(SetUpUserDataDirectory())
      << "Could not set up user data directory.";

  CommandLine* command_line = CommandLine::ForCurrentProcess();
  SetUpCommandLine(command_line);
  PrepareTestCommandLine(command_line);

  if (command_line->HasSwitch(switches::kSingleProcess)) {
    content::RenderProcessHost::set_run_renderer_in_process(true);
    single_process_renderer_client_.reset(
        new content::MockContentRendererClient);
    content::GetContentClient()->set_renderer(
        single_process_renderer_client_.get());
  }

#if defined(OS_CHROMEOS)
  FilePath log_dir = logging::GetSessionLogFile(*command_line).DirName();
  file_util::CreateDirectory(log_dir);
#endif  // defined(OS_CHROMEOS)

  host_resolver_ = new net::RuleBasedHostResolverProc(NULL);

  host_resolver_->AddSimulatedFailure("*.google.com");

  host_resolver_->AddSimulatedFailure("wpad");

  net::ScopedDefaultHostResolverProc scoped_host_resolver_proc(
      host_resolver_.get());

  BrowserTestBase::SetUp();
}
