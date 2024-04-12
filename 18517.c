void RenderView::OnSwapOut(const ViewMsg_SwapOut_Params& params) {
  if (is_swapped_out_)
    return;


  SyncNavigationState();

  webview()->dispatchUnloadEvent();

  SetSwappedOut(true);

  webview()->mainFrame()->loadHTMLString(std::string(),
                                         GURL("about:swappedout"),
                                         GURL("about:swappedout"),
                                         false);

  Send(new ViewHostMsg_SwapOut_ACK(routing_id_, params));
}
