void PasswordStoreLoginsChangedObserver::Init() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  BrowserThread::PostTask(
      BrowserThread::DB,
      FROM_HERE,
      base::Bind(&PasswordStoreLoginsChangedObserver::RegisterObserversTask,
                 this));
  done_event_.Wait();
}
