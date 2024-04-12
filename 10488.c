  std::unique_ptr<content::WebContents> CreateAndNavigateWebContents() {
    std::unique_ptr<content::WebContents> web_contents =
        CreateTestWebContents();
    ResourceCoordinatorTabHelper::CreateForWebContents(web_contents.get());
    content::WebContentsTester::For(web_contents.get())
        ->NavigateAndCommit(GURL("https://www.example.com"));
    return web_contents;
  }
