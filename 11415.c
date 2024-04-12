DownloadItemImpl::RequestInfo::RequestInfo(
    const std::vector<GURL>& url_chain,
    const GURL& referrer_url,
    const GURL& site_url,
    const GURL& tab_url,
    const GURL& tab_referrer_url,
    const std::string& suggested_filename,
    const base::FilePath& forced_file_path,
    ui::PageTransition transition_type,
    bool has_user_gesture,
    const std::string& remote_address,
    base::Time start_time)
    : url_chain(url_chain),
      referrer_url(referrer_url),
      site_url(site_url),
      tab_url(tab_url),
      tab_referrer_url(tab_referrer_url),
      suggested_filename(suggested_filename),
      forced_file_path(forced_file_path),
      transition_type(transition_type),
      has_user_gesture(has_user_gesture),
      remote_address(remote_address),
      start_time(start_time) {}
