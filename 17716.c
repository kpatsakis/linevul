void ExtensionWindowLastFocusedTest::SetUpOnMainThread() {
  ExtensionTabsTest::SetUpOnMainThread();
  extension_ = ExtensionBuilder("Test").Build();
}
