  void VerifyProcessPriority(content::RenderProcessHost* process,
                             bool expected_is_backgrounded) {
    EXPECT_TRUE(process->IsInitializedAndNotDead());
    EXPECT_EQ(expected_is_backgrounded, process->IsProcessBackgrounded());

    if (base::Process::CanBackgroundProcesses()) {
      base::Process p = ProcessFromHandle(process->GetProcess().Handle());
      ASSERT_TRUE(p.IsValid());
#if defined(OS_MACOSX)
      base::PortProvider* port_provider =
          content::BrowserChildProcessHost::GetPortProvider();
      EXPECT_EQ(expected_is_backgrounded,
                p.IsProcessBackgrounded(port_provider));
#else
      EXPECT_EQ(expected_is_backgrounded, p.IsProcessBackgrounded());
#endif
    }
  }
