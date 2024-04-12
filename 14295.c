void NavigateToDataURLAndCheckForTerminationDisabler(
    Shell* shell,
    const std::string& html,
    bool expect_onunload,
    bool expect_onbeforeunload) {
  NavigateToURL(shell, GURL("data:text/html," + html));
  RenderFrameHostImpl* rfh =
      static_cast<RenderFrameHostImpl*>(shell->web_contents()->GetMainFrame());
  EXPECT_EQ(expect_onunload,
            rfh->GetSuddenTerminationDisablerState(blink::kUnloadHandler));
  EXPECT_EQ(expect_onbeforeunload, rfh->GetSuddenTerminationDisablerState(
                                       blink::kBeforeUnloadHandler));
}
