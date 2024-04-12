void RenderViewImpl::didLoseWebGLContext(
    WebKit::WebFrame* frame,
    int arb_robustness_status_code) {
  Send(new ViewHostMsg_DidLose3DContext(
      GURL(frame->top()->document().securityOrigin().toString()),
      THREE_D_API_TYPE_WEBGL,
      arb_robustness_status_code));
}
