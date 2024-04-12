DownloadManagerImpl::DownloadManagerImpl(BrowserContext* browser_context)
    : item_factory_(new DownloadItemFactoryImpl()),
      shutdown_needed_(true),
      initialized_(false),
      history_db_initialized_(false),
      in_progress_cache_initialized_(false),
      browser_context_(browser_context),
      delegate_(nullptr),
      in_progress_manager_(
          browser_context_->RetriveInProgressDownloadManager()),
      next_download_id_(download::DownloadItem::kInvalidId),
      is_history_download_id_retrieved_(false),
      should_persist_new_download_(false),
      cancelled_download_cleared_from_history_(0),
      interrupted_download_cleared_from_history_(0),
      weak_factory_(this) {
  DCHECK(browser_context);
  download::SetIOTaskRunner(
      base::CreateSingleThreadTaskRunnerWithTraits({BrowserThread::IO}));
  if (!base::FeatureList::IsEnabled(network::features::kNetworkService))
    download::UrlDownloadHandlerFactory::Install(new UrlDownloaderFactory());

  if (!in_progress_manager_) {
    in_progress_manager_ =
        std::make_unique<download::InProgressDownloadManager>(
            this,
            IsOffTheRecord() ? base::FilePath() : browser_context_->GetPath(),
            base::BindRepeating(&IsOriginSecure),
            base::BindRepeating(&DownloadRequestUtils::IsURLSafe));
  } else {
    in_progress_manager_->set_delegate(this);
    in_progress_manager_->set_download_start_observer(nullptr);
    in_progress_manager_->set_is_origin_secure_cb(
        base::BindRepeating(&IsOriginSecure));
  }
  in_progress_manager_->NotifyWhenInitialized(base::BindOnce(
      &DownloadManagerImpl::OnInProgressDownloadManagerInitialized,
      weak_factory_.GetWeakPtr()));
}
