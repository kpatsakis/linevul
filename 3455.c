  SearchProviderTest()
      : default_t_url_(NULL),
        term1_(UTF8ToUTF16("term1")),
        keyword_t_url_(NULL),
        keyword_term_(UTF8ToUTF16("keyword")),
        io_thread_(ChromeThread::IO),
        quit_when_done_(false) {
    io_thread_.Start();
  }
