  Message GetNextMessage() {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

    if (messages_.empty()) {
      base::RunLoop run_loop;
      quit_closure_ = run_loop.QuitClosure();
      run_loop.Run();
    }

    DCHECK(!messages_.empty());
    const Message next = messages_.front();
    messages_.pop_front();
    return next;
  }
