  const GURL& GetLastUrl() {
    download_run_loop_.Run();
    return last_url_;
  }
