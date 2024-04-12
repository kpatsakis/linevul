void TestingAutomationProvider::OnBrowserRemoved(const Browser* browser) {
  if (BrowserList::empty() && !CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kKeepAliveForTest)) {
    MessageLoop::current()->PostTask(
        FROM_HERE,
        base::Bind(&TestingAutomationProvider::OnRemoveProvider, this));
  }
}
