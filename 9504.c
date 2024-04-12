  void VerifyProcessIsForegrounded(WebContents* web_contents) {
    constexpr bool kExpectedIsBackground = false;
    VerifyProcessPriority(web_contents->GetMainFrame()->GetProcess(),
                          kExpectedIsBackground);
  }
