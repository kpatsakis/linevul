void SessionModelAssociator::InitializeCurrentSessionName() {
  DCHECK(CalledOnValidThread());
  if (setup_for_test_) {
    OnSessionNameInitialized("TestSessionName");
  } else {
#if defined(OS_CHROMEOS)
    OnSessionNameInitialized("Chromebook");
#else
    BrowserThread::PostTask(BrowserThread::FILE, FROM_HERE,
        new GetSessionNameTask(MakeWeakHandle(AsWeakPtr())));
#endif
  }
}
