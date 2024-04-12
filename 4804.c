TestBackgroundLoaderOffliner::TestBackgroundLoaderOffliner(
    content::BrowserContext* browser_context,
    const OfflinerPolicy* policy,
    OfflinePageModel* offline_page_model,
    std::unique_ptr<LoadTerminationListener> load_termination_listener)
    : BackgroundLoaderOffliner(browser_context,
                               policy,
                               offline_page_model,
                               std::move(load_termination_listener)) {}
