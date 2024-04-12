  void TryCreateDuplicateRequestIds(Shell* shell, bool block_loaders) {
    NavigateToURL(shell, GURL("http://foo.com/simple_page.html"));
    RenderFrameHostImpl* rfh = static_cast<RenderFrameHostImpl*>(
        shell->web_contents()->GetMainFrame());

    if (block_loaders) {
      rfh->BlockRequestsForFrame();
    }

    const char* blocking_url = net::URLRequestSlowDownloadJob::kUnknownSizeUrl;
    network::ResourceRequest request(CreateXHRRequest(blocking_url));

    RenderProcessHostKillWaiter kill_waiter(rfh->GetProcess());
    network::mojom::URLLoaderPtr loader1, loader2;
    network::TestURLLoaderClient client1, client2;

    CreateLoaderAndStart(rfh, mojo::MakeRequest(&loader1), rfh->GetRoutingID(),
                         kRequestIdNotPreviouslyUsed, request,
                         client1.CreateInterfacePtr().PassInterface());
    CreateLoaderAndStart(rfh, mojo::MakeRequest(&loader2), rfh->GetRoutingID(),
                         kRequestIdNotPreviouslyUsed, request,
                         client2.CreateInterfacePtr().PassInterface());
    EXPECT_EQ(bad_message::RDH_INVALID_REQUEST_ID, kill_waiter.Wait());
  }
