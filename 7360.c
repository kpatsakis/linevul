void ComponentUpdaterPolicyTest::BeginTest() {
  cus_ = g_browser_process->component_updater();

  const auto config = component_updater::MakeChromeComponentUpdaterConfigurator(
      base::CommandLine::ForCurrentProcess(), g_browser_process->local_state());
  const auto urls = config->UpdateUrl();
  ASSERT_TRUE(urls.size());
  const GURL url = urls.front();

  cur_test_case_ = std::make_pair(
      &ComponentUpdaterPolicyTest::DefaultPolicy_GroupPolicySupported,
      &ComponentUpdaterPolicyTest::FinishDefaultPolicy_GroupPolicySupported);

  CallAsync(cur_test_case_.first);
}
