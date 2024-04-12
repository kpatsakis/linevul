bool ShellMainDelegate::BasicStartupComplete(int* exit_code) {
  base::CommandLine& command_line = *base::CommandLine::ForCurrentProcess();
  int dummy;
  if (!exit_code)
    exit_code = &dummy;

#if defined(OS_WIN)
  logging::LogEventProvider::Initialize(kContentShellProviderName);

  v8_breakpad_support::SetUp();
#endif
#if defined(OS_LINUX)
  breakpad::SetFirstChanceExceptionHandler(v8::V8::TryHandleSignal);
#endif
#if defined(OS_MACOSX)
  OverrideFrameworkBundlePath();
  OverrideChildProcessPath();
  OverrideSourceRootPath();
  EnsureCorrectResolutionSettings();
#endif  // OS_MACOSX

  InitLogging(command_line);

  if (command_line.HasSwitch(switches::kCheckLayoutTestSysDeps)) {
    if (!CheckLayoutSystemDeps()) {
      *exit_code = 1;
      return true;
    }
  }

  if (command_line.HasSwitch("run-layout-test")) {
    std::cerr << std::string(79, '*') << "\n"
              << "* The flag --run-layout-test is obsolete. Please use --"
              << switches::kRunWebTests << " instead. *\n"
              << std::string(79, '*') << "\n";
    command_line.AppendSwitch(switches::kRunWebTests);
  }

  if (command_line.HasSwitch(switches::kRunWebTests)) {
    EnableBrowserLayoutTestMode();

#if BUILDFLAG(ENABLE_PLUGINS)
    if (!ppapi::RegisterBlinkTestPlugin(&command_line)) {
      *exit_code = 1;
      return true;
    }
#endif
    command_line.AppendSwitch(switches::kDisableResizeLock);
    command_line.AppendSwitch(cc::switches::kEnableGpuBenchmarking);
    command_line.AppendSwitch(switches::kEnableLogging);
    command_line.AppendSwitch(switches::kAllowFileAccessFromFiles);
    if (!command_line.HasSwitch(switches::kUseGpuInTests) &&
        !command_line.HasSwitch(switches::kUseGL)) {
      command_line.AppendSwitchASCII(
          switches::kUseGL,
          gl::GetGLImplementationName(gl::GetSoftwareGLImplementation()));
    }
    command_line.AppendSwitchASCII(
        switches::kTouchEventFeatureDetection,
        switches::kTouchEventFeatureDetectionEnabled);
    if (!command_line.HasSwitch(switches::kForceDeviceScaleFactor))
      command_line.AppendSwitchASCII(switches::kForceDeviceScaleFactor, "1.0");

    if (!command_line.HasSwitch(switches::kAutoplayPolicy)) {
      command_line.AppendSwitchASCII(
          switches::kAutoplayPolicy,
          switches::autoplay::kNoUserGestureRequiredPolicy);
    }

    if (!command_line.HasSwitch(switches::kStableReleaseMode)) {
      command_line.AppendSwitch(
        switches::kEnableExperimentalWebPlatformFeatures);
    }

    if (!command_line.HasSwitch(switches::kEnableThreadedCompositing)) {
      command_line.AppendSwitch(switches::kDisableThreadedCompositing);
      command_line.AppendSwitch(cc::switches::kDisableThreadedAnimation);
    }

    if (command_line.HasSwitch(switches::kEnableDisplayCompositorPixelDump)) {
      command_line.AppendSwitch(switches::kRunAllCompositorStagesBeforeDraw);
      command_line.AppendSwitch(cc::switches::kDisableCheckerImaging);
    }

    command_line.AppendSwitch(switches::kEnableInbandTextTracks);
    command_line.AppendSwitch(switches::kMuteAudio);

    command_line.AppendSwitch(switches::kEnablePreciseMemoryInfo);

    command_line.AppendSwitchASCII(network::switches::kHostResolverRules,
                                   "MAP *.test 127.0.0.1");

    command_line.AppendSwitch(switches::kEnablePartialRaster);
    command_line.AppendSwitch(switches::kEnableWebAuthTestingAPI);

    if (!command_line.HasSwitch(switches::kForceGpuRasterization) &&
        !command_line.HasSwitch(switches::kEnableGpuRasterization)) {
      command_line.AppendSwitch(switches::kDisableGpuRasterization);
    }

    if (!command_line.HasSwitch(switches::kForceColorProfile))
      command_line.AppendSwitchASCII(switches::kForceColorProfile, "srgb");

    command_line.AppendSwitch(switches::kDisableSkiaRuntimeOpts);

    command_line.AppendSwitch(switches::kDisallowNonExactResourceReuse);

    command_line.AppendSwitch(switches::kUseFakeUIForMediaStream);
    command_line.AppendSwitch(switches::kUseFakeDeviceForMediaStream);

    if (!BlinkTestPlatformInitialize()) {
      *exit_code = 1;
      return true;
    }
  }

  content_client_.reset(switches::IsRunWebTestsSwitchPresent()
                            ? new LayoutTestContentClient
                            : new ShellContentClient);
  SetContentClient(content_client_.get());

  return false;
}
