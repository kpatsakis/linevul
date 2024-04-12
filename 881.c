void NaClProcessHost::OnChildDied() {
#if defined(OS_WIN)
  NaClBrokerService::GetInstance()->OnLoaderDied();
#endif
  BrowserChildProcessHost::OnChildDied();
}
