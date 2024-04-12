  bool HistoryContainsURL(const GURL& url) {
    scoped_refptr<content::MessageLoopRunner> message_loop_runner =
        new content::MessageLoopRunner;
    quit_closure_ = message_loop_runner->QuitClosure();
    history_service_->QueryURL(
        url,
        true,
        base::Bind(&RemoveHistoryTester::SaveResultAndQuit,
                   base::Unretained(this)),
        &tracker_);
    message_loop_runner->Run();
    return query_url_success_;
  }
