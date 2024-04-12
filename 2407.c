  explicit ClosePageBeforeCommitHelper(WebContents* web_contents)
      : DidCommitProvisionalLoadInterceptor(web_contents) {}
