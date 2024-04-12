  explicit RenderFrameCreatedObserver(Shell* shell)
      : WebContentsObserver(shell->web_contents()), last_rfh_(nullptr) {}
