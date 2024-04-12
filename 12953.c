  void RequestFaviconSyncForPageURL(const GURL& page_url) {
    base::RunLoop run_loop;
    quit_closure_ = run_loop.QuitClosure();
    favicon_service_->GetRawFaviconForPageURL(
        page_url, {favicon_base::IconType::kFavicon}, gfx::kFaviconSize,
        /*fallback_to_host=*/false,
        base::Bind(&RemoveFaviconTester::SaveResultAndQuit,
                   base::Unretained(this)),
        &tracker_);
    run_loop.Run();
  }
